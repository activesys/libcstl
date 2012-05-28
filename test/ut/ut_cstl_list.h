#ifndef _UT_CSTL_LIST_H_
#define _UT_CSTL_LIST_H_

UT_SUIT_DECLARATION(cstl_list)

/*
 * test list_init
 */
UT_CASE_DECLARATION(list_init)
void test_list_init__null_list_container(void** state);
void test_list_init__non_created_list_container(void** state);
void test_list_init__successfully(void** state);
/*
 * test list_init_n
 */
UT_CASE_DECLARATION(list_init_n)
void test_list_init_n__null_list_container(void** state);
void test_list_init_n__non_created_list_container(void** state);
void test_list_init_n__empty(void** state);
void test_list_init_n__c_builtin(void** state);
void test_list_init_n__cstr(void** stat);
void test_list_init_n__libcstl_builtin(void** state);
void test_list_init_n__user_define(void** state);
/*
 * test list_destroy
 */
UT_CASE_DECLARATION(list_destroy)
void test_list_destroy__null_list_container(void** state);
void test_list_destroy__non_created_list_container(void** state);
void test_list_destroy__created_non_inited(void** state);
void test_list_destroy__empty(void** state);
void test_list_destroy__non_empty(void** state);
/*
 * test list_init_copy
 */
UT_CASE_DECLARATION(list_init_copy)
void test_list_init_copy__null_dest_list_container(void** state);
void test_list_init_copy__null_src_list_container(void** state);
void test_list_init_copy__non_created_dest_list_container(void** state);
void test_list_init_copy__non_inited_src_list_container(void** state);
void test_list_init_copy__not_same_type(void** state);
void test_list_init_copy__init_copy_empty(void** state);
void test_list_init_copy__c_builtin(void** state);
void test_list_init_copy__cstr(void** state);
void test_list_init_copy__libcstl_builtin(void** state);
void test_list_init_copy__user_define(void** state);
/*
 * test list_init_copy_range
 */
UT_CASE_DECLARATION(list_init_copy_range)
void test_list_init_copy_range__null_list_container(void** state);
void test_list_init_copy_range__non_created_list_container(void** state);
void test_list_init_copy_range__invalid_range(void** state);
void test_list_init_copy_range__not_same(void** state);
void test_list_init_copy_range__init_copy_range_empty(void** state);
void test_list_init_copy_range__c_builtin(void** state);
void test_list_init_copy_range__cstr(void** state);
void test_list_init_copy_range__libcstl_builtin(void** state);
void test_list_init_copy_range__user_define(void** state);
void test_list_init_copy_range__other_container_range(void** state);
void test_list_init_copy_range__other_container_range1(void** state);
/*
 * test list_init_copy_array
 */
UT_CASE_DECLARATION(list_init_copy_array)
void test_list_init_copy_array__null_list_container(void** state);
void test_list_init_copy_array__non_created_list_container(void** state);
void test_list_init_copy_array__invalid_array(void** state);
void test_list_init_copy_array__init_copy_array_empty(void** state);
void test_list_init_copy_array__c_builtin(void** state);
void test_list_init_copy_array__cstr(void** state);
void test_list_init_copy_array__libcstl_builtin(void** state);
void test_list_init_copy_array__user_define(void** state);
/*
 * test list_size
 */
UT_CASE_DECLARATION(list_size)
void test_list_size__null_list_container(void** state);
void test_list_size__non_inited_list_container(void** state);
void test_list_size__empty(void** state);
void test_list_size__non_empty(void** state);
/*
 * test list_empty
 */
UT_CASE_DECLARATION(list_empty)
void test_list_empty__null_list_container(void** state);
void test_list_empty__non_inited_list_container(void** state);
void test_list_empty__empty(void** state);
void test_list_empty__non_empty(void** state);
/*
 * test list_max_size
 */
UT_CASE_DECLARATION(list_max_size)
void test_list_max_size__null_list_container(void** state);
void test_list_max_size__non_inited_list_container(void** state);
void test_list_max_size__empty(void** state);
void test_list_max_size__non_empty(void** state);
/*
 * test list_equal
 */
UT_CASE_DECLARATION(list_equal)
void test_list_equal__null_first(void** state);
void test_list_equal__null_second(void** state);
void test_list_equal__non_inited_first(void** state);
void test_list_equal__non_inited_second(void** state);
void test_list_equal__not_same_type(void** state);
void test_list_equal__same_list(void** state);
void test_list_equal__size_first_less_than_second(void** state);
void test_list_equal__size_first_greater_than_second(void** state);
void test_list_equal__size_equal_0(void** state);
void test_list_equal__size_equal_elem_first_less_than_second(void** state);
void test_list_equal__size_equal_elem_first_greater_than_second(void** state);
void test_list_equal__size_equal_elem_equal(void** state);
/*
 * test list_not_equal
 */
UT_CASE_DECLARATION(list_not_equal)
void test_list_not_equal__null_first(void** state);
void test_list_not_equal__null_second(void** state);
void test_list_not_equal__non_inited_first(void** state);
void test_list_not_equal__non_inited_second(void** state);
void test_list_not_equal__not_same_type(void** state);
void test_list_not_equal__same_list(void** state);
void test_list_not_equal__size_first_less_than_second(void** state);
void test_list_not_equal__size_first_greater_than_second(void** state);
void test_list_not_equal__size_equal_0(void** state);
void test_list_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_list_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_list_not_equal__size_equal_elem_equal(void** state);
/*
 * test list_less
 */
UT_CASE_DECLARATION(list_less)
void test_list_less__null_first(void** state);
void test_list_less__null_second(void** state);
void test_list_less__non_inited_first(void** state);
void test_list_less__non_inited_second(void** state);
void test_list_less__not_same_type(void** state);
void test_list_less__same_list(void** state);
void test_list_less__size_first_less_than_second(void** state);
void test_list_less__size_first_greater_than_second(void** state);
void test_list_less__size_equal_0(void** state);
void test_list_less__size_equal_elem_first_less_than_second(void** state);
void test_list_less__size_equal_elem_first_greater_than_second(void** state);
void test_list_less__size_equal_elem_equal(void** state);
/*
 * test list_less_equal
 */
UT_CASE_DECLARATION(list_less_equal)
void test_list_less_equal__null_first(void** state);
void test_list_less_equal__null_second(void** state);
void test_list_less_equal__non_inited_first(void** state);
void test_list_less_equal__non_inited_second(void** state);
void test_list_less_equal__not_same_type(void** state);
void test_list_less_equal__same_list(void** state);
void test_list_less_equal__size_first_less_than_second(void** state);
void test_list_less_equal__size_first_greater_than_second(void** state);
void test_list_less_equal__size_equal_0(void** state);
void test_list_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_list_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_list_less_equal__size_equal_elem_equal(void** state);
/*
 * test list_greater
 */
UT_CASE_DECLARATION(list_greater)
void test_list_greater__null_first(void** state);
void test_list_greater__null_second(void** state);
void test_list_greater__non_inited_first(void** state);
void test_list_greater__non_inited_second(void** state);
void test_list_greater__not_same_type(void** state);
void test_list_greater__same_list(void** state);
void test_list_greater__size_first_less_than_second(void** state);
void test_list_greater__size_first_greater_than_second(void** state);
void test_list_greater__size_equal_0(void** state);
void test_list_greater__size_equal_elem_first_less_than_second(void** state);
void test_list_greater__size_equal_elem_first_greater_than_second(void** state);
void test_list_greater__size_equal_elem_equal(void** state);
/*
 * test list_greater_equal
 */
UT_CASE_DECLARATION(list_greater_equal)
void test_list_greater_equal__null_first(void** state);
void test_list_greater_equal__null_second(void** state);
void test_list_greater_equal__non_inited_first(void** state);
void test_list_greater_equal__non_inited_second(void** state);
void test_list_greater_equal__not_same_type(void** state);
void test_list_greater_equal__same_list(void** state);
void test_list_greater_equal__size_first_less_than_second(void** state);
void test_list_greater_equal__size_first_greater_than_second(void** state);
void test_list_greater_equal__size_equal_0(void** state);
void test_list_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_list_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_list_greater_equal__size_equal_elem_equal(void** state);
/*
 * test list_assign
 */
UT_CASE_DECLARATION(list_assign)
void test_list_assign__null_dest(void** state);
void test_list_assign__null_src(void** state);
void test_list_assign__non_inited_dest(void** state);
void test_list_assign__non_inited_src(void** state);
void test_list_assign__not_same_type(void** state);
void test_list_assign__same_container(void** state);
void test_list_assign__0_assign_0(void** state);
void test_list_assign__0_assign_10(void** state);
void test_list_assign__10_assign_0(void** state);
void test_list_assign__10_assign_10_list_equal(void** state);
void test_list_assign__10_assign_10_list_not_equal(void** state);
void test_list_assign__10_assign_1000(void** state);
/*
 * test list_assign_range
 */
UT_CASE_DECLARATION(list_assign_range)
void test_list_assign_range__null_list_container(void** state);
void test_list_assign_range__non_inited(void** state);
void test_list_assign_range__invalid_it_begin(void** state);
void test_list_assign_range__invalid_it_end(void** state);
void test_list_assign_range__invalid_range(void** state);
void test_list_assign_range__invalid_range_not_same_type(void** state);
void test_list_assign_range__range_belong_to_list(void** state);
void test_list_assign_range__0_assign_range_0(void** state);
void test_list_assign_range__0_assign_range_10(void** state);
void test_list_assign_range__10_assign_range_0(void** state);
void test_list_assign_range__10_assign_range_10_same_elem(void** state);
void test_list_assign_range__10_assign_range_10_not_same_elem(void** state);
void test_list_assign_range__10_assign_range_1000(void** state);
void test_list_assign_range__other_container_range(void** state);
/*
 * test list_assign_array
 */
UT_CASE_DECLARATION(list_assign_array)
void test_list_assign_array__null_list_container(void** state);
void test_list_assign_array__non_inited(void** state);
void test_list_assign_array__invalid_array(void** state);
void test_list_assign_array__0_assign_array_0(void** state);
void test_list_assign_array__0_assign_array_10(void** state);
void test_list_assign_array__10_assign_array_0(void** state);
void test_list_assign_array__10_assign_array_10_same_elem(void** state);
void test_list_assign_array__10_assign_array_10_not_same_elem(void** state);
void test_list_assign_array__10_assign_array_1000(void** state);
void test_list_assign_array__cstr(void** state);
void test_list_assign_array__user_define(void** state);
void test_list_assign_array__cstl_builtin(void** state);
/*
 * test list_swap
 */
UT_CASE_DECLARATION(list_swap)
void test_list_swap__null_first(void** state);
void test_list_swap__null_second(void** state);
void test_list_swap__non_inited_first(void** state);
void test_list_swap__non_inited_second(void** state);
void test_list_swap__not_same_type(void** state);
void test_list_swap__list_equal(void** state);
void test_list_swap__0_swap_10(void** state);
void test_list_swap__10_swap_0(void** state);
void test_list_swap__10_swap_10(void** state);
void test_list_swap__10_swap_1000(void** state);
/*
 * test list_front
 */
UT_CASE_DECLARATION(list_front)
void test_list_front__null_list_container(void** state);
void test_list_front__non_inited_list_container(void** state);
void test_list_front__empty(void** state);
void test_list_front__successfully(void** state);
void test_list_front__successfully_cstr(void** state);
/*
 * test list_back
 */
UT_CASE_DECLARATION(list_back)
void test_list_back__null_list_container(void** state);
void test_list_back__non_inited_list_container(void** state);
void test_list_back__empty(void** state);
void test_list_back__successfully(void** state);
void test_list_back__successfully_cstr(void** state);
/*
 * test list_begin
 */
UT_CASE_DECLARATION(list_begin)
void test_list_begin__null_list_container(void** state);
void test_list_begin__non_inited_list_container(void** state);
void test_list_begin__empty(void** state);
void test_list_begin__non_empty(void** state);
/*
 * test list_end
 */
UT_CASE_DECLARATION(list_end)
void test_list_end__null_list_container(void** state);
void test_list_end__non_inited_list_container(void** state);
void test_list_end__empty(void** state);
void test_list_end__non_empty(void** state);
/*
 * test list_insert_range
 */
UT_CASE_DECLARATION(list_insert_range)
void test_list_insert_range__null_list_container(void** state);
void test_list_insert_range__non_inited(void** state);
void test_list_insert_range__invalid_position(void** state);
void test_list_insert_range__invalid_range(void** state);
void test_list_insert_range__invalid_range_not_same_type(void** state);
void test_list_insert_range__invalid_range_belong_to_list(void** state);
void test_list_insert_range__empty_insert_0(void** state);
void test_list_insert_range__empty_insert_10(void** state);
void test_list_insert_range__begin_insert_0(void** state);
void test_list_insert_range__begin_insert_10(void** state);
void test_list_insert_range__middle_insert_0(void** state);
void test_list_insert_range__middle_insert_10(void** state);
void test_list_insert_range__end_insert_0(void** state);
void test_list_insert_range__end_insert_10(void** state);
void test_list_insert_range__other_container_range(void** state);
/*
 * test list_insert_array
 */
UT_CASE_DECLARATION(list_insert_array)
void test_list_insert_array__null_list_container(void** state);
void test_list_insert_array__non_inited(void** state);
void test_list_insert_array__invalid_position(void** state);
void test_list_insert_array__invalid_array(void** state);
void test_list_insert_array__empty_insert_0(void** state);
void test_list_insert_array__empty_insert_10(void** state);
void test_list_insert_array__begin_insert_0(void** state);
void test_list_insert_array__begin_insert_10(void** state);
void test_list_insert_array__middle_insert_0(void** state);
void test_list_insert_array__middle_insert_10(void** state);
void test_list_insert_array__end_insert_0(void** state);
void test_list_insert_array__end_insert_10(void** state);
void test_list_insert_array__cstr(void** state);
void test_list_insert_array__cstl(void** state);
void test_list_insert_array__user_define(void** state);
/*
 * test list_pop_back
 */
UT_CASE_DECLARATION(list_pop_back)
void test_list_pop_back__null_list_container(void** state);
void test_list_pop_back__non_inited_list_container(void** state);
void test_list_pop_back__empty(void** state);
void test_list_pop_back__successfully(void** state);
/*
 * test list_pop_front
 */
UT_CASE_DECLARATION(list_pop_front)
void test_list_pop_front__null_list_container(void** state);
void test_list_pop_front__non_inited_list_container(void** state);
void test_list_pop_front__empty(void** state);
void test_list_pop_front__successfully(void** state);
/*
 * test list_erase
 */
UT_CASE_DECLARATION(list_erase)
void test_list_erase__null_list_container(void** state);
void test_list_erase__non_inited_list_container(void** state);
void test_list_erase__invalid_pos_end(void** state);
void test_list_erase__invalid_pos(void** state);
void test_list_erase__successfully_begin(void** state);
void test_list_erase__successfully_middle(void** state);
void test_list_erase__successfully_back(void** state);
/*
 * test list_erase_range
 */
UT_CASE_DECLARATION(list_erase_range)
void test_list_erase_range__null_list_container(void** state);
void test_list_erase_range__non_inited_list_container(void** state);
void test_list_erase_range__invalid_range_not_belong_to_list(void** state);
void test_list_erase_range__invalid_range(void** state);
void test_list_erase_range__successfully_empty(void** state);
void test_list_erase_range__successfully_begin(void** state);
void test_list_erase_range__successfully_middle(void** state);
void test_list_erase_range__successfully_end(void** state);
void test_list_erase_range__successfully_all(void** state);
/*
 * test list_remove_if
 */
UT_CASE_DECLARATION(list_remove_if)
void test_list_remove_if__null_list_container(void** state);
void test_list_remove_if__non_inited_list_container(void** state);
void test_list_remove_if__empty(void** state);
void test_list_remove_if__non_empty_no_removed(void** state);
void test_list_remove_if__non_empty_remove(void** state);
void test_list_remove_if__non_empty_remove_more(void** state);
void test_list_remove_if__non_empty_remove_all(void** state);
void test_list_remove_if__empty_default_ufun_op(void** state);
void test_list_remove_if__non_empty_default_ufun_op(void** state);
void test_list_remove_if__cstr_empty(void** state);
void test_list_remove_if__cstr_non_empty_no_removed(void** state);
void test_list_remove_if__cstr_non_empty_remove(void** state);
void test_list_remove_if__cstr_non_empty_remove_more(void** state);
void test_list_remove_if__cstr_non_empty_remove_all(void** state);
/*
 * test list_resize
 */
UT_CASE_DECLARATION(list_resize)
void test_list_resize__null_list_container(void** state);
void test_list_resize__non_inited(void** state);
void test_list_resize__successfully_0_resize_0(void** state);
void test_list_resize__successfully_0_resize_10(void** state);
void test_list_resize__successfully_10_resize_0(void** state);
void test_list_resize__successfully_10_resize_10(void** state);
void test_list_resize__successfully_10_resize_1000(void** state);
/*
 * test list_clear
 */
UT_CASE_DECLARATION(list_clear)
void test_list_clear__null_list_container(void** state);
void test_list_clear__non_inited_list_container(void** state);
void test_list_clear__empty_list_container(void** state);
void test_list_clear__non_empty_list_container(void** state);
/*
 * test list_unique
 */
UT_CASE_DECLARATION(list_unique)
void test_list_unique__null_list_container(void** state);
void test_list_unique__non_inited_list_container(void** state);
void test_list_unique__empty(void** state);
void test_list_unique__non_empty_no_duplicate(void** state);
void test_list_unique__non_empty_adjacent_duplicate(void** state);
void test_list_unique__non_empty_not_adjacent_duplicate(void** state);
void test_list_unique__non_empty_all_duplicate(void** state);
void test_list_unique__cstr_non_empty_no_duplicate(void** state);
void test_list_unique__cstr_non_empty_adjacent_duplicate(void** state);
void test_list_unique__cstr_non_empty_not_adjacent_duplicate(void** state);
void test_list_unique__cstr_non_empty_all_duplicate(void** state);
/*
 * test list_unique_if
 */
UT_CASE_DECLARATION(list_unique_if)
void test_list_unique_if__null_list_container(void** state);
void test_list_unique_if__non_inited_list_container(void** state);
void test_list_unique_if__empty(void** state);
void test_list_unique_if__non_empty_non_duplicate(void** state);
void test_list_unique_if__non_empty_duplicate(void** state);
void test_list_unique_if__non_empty_more_duplicate(void** state);
void test_list_unique_if__non_empty_duplicate_not_adjacent(void** state);
void test_list_unique_if__non_empty_duplicate_all(void** state);
void test_list_unique_if__cstr_non_empty_no_duplicate(void** state);
void test_list_unique_if__cstr_non_empty_adjacent_duplicate(void** state);
void test_list_unique_if__cstr_non_empty_not_adjacent_duplicate(void** state);
void test_list_unique_if__cstr_non_empty_all_duplicate(void** state);
void test_list_unique_if__default_predicate(void** state);
/*
 * test list_splice
 */
UT_CASE_DECLARATION(list_splice)
void test_list_splice__null_target_list_container(void** state);
void test_list_splice__null_source_list_container(void** state);
void test_list_splice__non_inited_target_list_container(void** state);
void test_list_splice__non_inited_source_list_container(void** state);
void test_list_splice__not_same_type(void** state);
void test_list_splice__invalid_target_position(void** state);
void test_list_splice__same_list(void** state);
void test_list_splice__target_empty_source_empty(void** state);
void test_list_splice__target_empty_source_non_empty(void** state);
void test_list_splice__target_begin_source_empty(void** state);
void test_list_splice__target_begin_source_non_empty(void** state);
void test_list_splice__target_middle_source_non_empty(void** state);
void test_list_splice__target_end_source_non_empty(void** state);
/*
 * test list_splice_pos
 */
UT_CASE_DECLARATION(list_splice_pos)
void test_list_splice_pos__null_target_list_container(void** state);
void test_list_splice_pos__null_source_list_container(void** state);
void test_list_splice_pos__non_inited_target_list_container(void** state);
void test_list_splice_pos__non_inited_source_list_container(void** state);
void test_list_splice_pos__not_same(void** state);
void test_list_splice_pos__invalid_tearget_position(void** state);
void test_list_splice_pos__invalid_source_position(void** state);
void test_list_splice_pos__invalid_source_position_end(void** state);
void test_list_splice_pos__same_list_container_same_position(void** state);
void test_list_splice_pos__same_list_container_next_position(void** state);
void test_list_splice_pos__same_list_container_not_same_not_next_position(void** state);
void test_list_splice_pos__target_empty(void** state);
void test_list_splice_pos__target_begin_source_begin(void** state);
void test_list_splice_pos__target_middle_source_middle(void** state);
void test_list_splice_pos__target_end_source_begin(void** state);
/*
 * test list_splice_range
 */
UT_CASE_DECLARATION(list_splice_range)
void test_list_splice_range__null_target_list_container(void** state);
void test_list_splice_range__null_source_list_container(void** state);
void test_list_splice_range__non_inited_target_list_container(void** state);
void test_list_splice_range__non_inited_source_list_container(void** state);
void test_list_splice_range__not_same(void** state);
void test_list_splice_range__invalid_tearget_position(void** state);
void test_list_splice_range__invalid_source_range(void** state);
void test_list_splice_range__invalid_target_position_in_range(void** state);
void test_list_splice_range__same_list_container_pos_equal_begin(void** state);
void test_list_splice_range__same_list_container_pos_equal_end(void** state);
void test_list_splice_range__same_list_container_pos_not_in_range(void** state);
void test_list_splice_range__target_empty_range_empty(void** state);
void test_list_splice_range__target_empty_range_not_empty(void** state);
void test_list_splice_range__target_begin_source_begin(void** state);
void test_list_splice_range__target_middle_source_middle(void** state);
void test_list_splice_range__target_end_source_all(void** state);
/*
 * test list_sort
 */
UT_CASE_DECLARATION(list_sort)
void test_list_sort__null_list_container(void** state);
void test_list_sort__non_inited_list_container(void** state);
void test_list_sort__empty_less(void** state);
void test_list_sort__1_less(void** state);
void test_list_sort__2_equal_less(void** state);
void test_list_sort__2_less_less(void** state);
void test_list_sort__2_greater_less(void** state);
void test_list_sort__random_equal_less(void** state);
void test_list_sort__random_less_less(void** state);
void test_list_sort__random_greater_less(void** state);
void test_list_sort__random_random_less(void** state);
void test_list_sort__random_random_dup_less(void** state);
/*
 * test list_sort_if
 */
UT_CASE_DECLARATION(list_sort_if)
void test_list_sort_if__null_list_container(void** state);
void test_list_sort_if__non_inited_list_container(void** state);
void test_list_sort_if__empty_less(void** state);
void test_list_sort_if__empty_greater(void** state);
void test_list_sort_if__1_less(void** state);
void test_list_sort_if__1_greater(void** state);
void test_list_sort_if__2_equal_less(void** state);
void test_list_sort_if__2_equal_greater(void** state);
void test_list_sort_if__2_less_less(void** state);
void test_list_sort_if__2_less_greater(void** state);
void test_list_sort_if__2_greater_less(void** state);
void test_list_sort_if__2_greater_greater(void** state);
void test_list_sort_if__random_equal_less(void** state);
void test_list_sort_if__random_equal_greater(void** state);
void test_list_sort_if__random_less_less(void** state);
void test_list_sort_if__random_less_greater(void** state);
void test_list_sort_if__random_greater_less(void** state);
void test_list_sort_if__random_greater_greater(void** state);
void test_list_sort_if__random_random_less(void** state);
void test_list_sort_if__random_random_greater(void** state);
void test_list_sort_if__random_random_dup_less(void** state);
void test_list_sort_if__random_random_dup_greater(void** state);
void test_list_sort_if__cstr_1_less(void** state);
void test_list_sort_if__cstr_1_greater(void** state);
void test_list_sort_if__cstr_2_equal_less(void** state);
void test_list_sort_if__cstr_2_equal_greater(void** state);
void test_list_sort_if__cstr_2_less_less(void** state);
void test_list_sort_if__cstr_2_less_greater(void** state);
void test_list_sort_if__cstr_2_greater_less(void** state);
void test_list_sort_if__cstr_2_greater_greater(void** state);
void test_list_sort_if__cstr_random_equal_less(void** state);
void test_list_sort_if__cstr_random_equal_greater(void** state);
void test_list_sort_if__cstr_random_less_less(void** state);
void test_list_sort_if__cstr_random_less_greater(void** state);
void test_list_sort_if__cstr_random_greater_less(void** state);
void test_list_sort_if__cstr_random_greater_greater(void** state);
void test_list_sort_if__cstr_random_random_less(void** state);
void test_list_sort_if__cstr_random_random_greater(void** state);
void test_list_sort_if__cstr_random_random_dup_less(void** state);
void test_list_sort_if__cstr_random_random_dup_greater(void** state);
/*
 * test list_merge
 */
UT_CASE_DECLARATION(list_merge)
void test_list_merge__null_dest_list_container(void** state);
void test_list_merge__null_src_list_container(void** state);
void test_list_merge__non_inited_dest_list_container(void** state);
void test_list_merge__non_inited_src_list_container(void** state);
void test_list_merge__not_same(void** state);
void test_list_merge__same_list_container(void** state);
void test_list_merge__dest_empty_src_empty(void** state);
void test_list_merge__dest_non_empty_src_empty(void** state);
void test_list_merge__dest_empty_src_non_empty(void** state);
void test_list_merge__dest_tailing(void** state);
void test_list_merge__src_tailing(void** state);
void test_list_merge__random(void** state);
void test_list_merge__cstr_dest_tailing(void** state);
void test_list_merge__cstr_src_tailing(void** state);
void test_list_merge__cstr_random(void** state);
/*
 * test list_merge_if
 */
UT_CASE_DECLARATION(list_merge_if)
void test_list_merge_if__null_dest_list_container(void** state);
void test_list_merge_if__null_src_list_container(void** state);
void test_list_merge_if__non_inited_dest_list_container(void** state);
void test_list_merge_if__non_inited_src_list_container(void** state);
void test_list_merge_if__not_same(void** state);
void test_list_merge_if__same_list_container(void** state);
void test_list_merge_if__dest_empty_src_empty(void** state);
void test_list_merge_if__dest_non_empty_src_empty(void** state);
void test_list_merge_if__dest_empty_src_non_empty(void** state);
void test_list_merge_if__ascending_dest_tailing(void** state);
void test_list_merge_if__ascending_src_tailing(void** state);
void test_list_merge_if__descending_dest_tailing(void** state);
void test_list_merge_if__descending_src_tailing(void** state);
void test_list_merge_if__random(void** state);
void test_list_merge_if__cstr_ascending_dest_tailing(void** state);
void test_list_merge_if__cstr_ascending_src_tailing(void** state);
void test_list_merge_if__cstr_descending_dest_tailing(void** state);
void test_list_merge_if__cstr_descending_src_tailing(void** state);
void test_list_merge_if__cstr_random(void** state);
/*
 * test list_reverse
 */
UT_CASE_DECLARATION(list_reverse)
void test_list_reverse__null_list_container(void** state);
void test_list_reverse__non_inited_list_container(void** state);
void test_list_reverse__empty(void** state);
void test_list_reverse__same(void** state);
void test_list_reverse__not_same(void** state);

#define UT_CSTL_LIST_CASE\
    UT_SUIT_BEGIN(cstl_list, test_list_init__null_list_container),\
    UT_CASE(test_list_init__non_created_list_container),\
    UT_CASE(test_list_init__successfully),\
    UT_CASE_BEGIN(list_init_n, test_list_init_n__null_list_container),\
    UT_CASE(test_list_init_n__non_created_list_container),\
    UT_CASE(test_list_init_n__empty),\
    UT_CASE(test_list_init_n__c_builtin),\
    UT_CASE(test_list_init_n__cstr),\
    UT_CASE(test_list_init_n__libcstl_builtin),\
    UT_CASE(test_list_init_n__user_define),\
    UT_CASE_BEGIN(list_destroy, test_list_destroy__null_list_container),\
    UT_CASE(test_list_destroy__non_created_list_container),\
    UT_CASE(test_list_destroy__created_non_inited),\
    UT_CASE(test_list_destroy__empty),\
    UT_CASE(test_list_destroy__non_empty),\
    UT_CASE_BEGIN(list_init_copy, test_list_init_copy__null_dest_list_container),\
    UT_CASE(test_list_init_copy__null_src_list_container),\
    UT_CASE(test_list_init_copy__non_created_dest_list_container),\
    UT_CASE(test_list_init_copy__non_inited_src_list_container),\
    UT_CASE(test_list_init_copy__not_same_type),\
    UT_CASE(test_list_init_copy__init_copy_empty),\
    UT_CASE(test_list_init_copy__c_builtin),\
    UT_CASE(test_list_init_copy__cstr),\
    UT_CASE(test_list_init_copy__libcstl_builtin),\
    UT_CASE(test_list_init_copy__user_define),\
    UT_CASE_BEGIN(list_init_copy_range, test_list_init_copy_range__null_list_container),\
    UT_CASE(test_list_init_copy_range__non_created_list_container),\
    UT_CASE(test_list_init_copy_range__invalid_range),\
    UT_CASE(test_list_init_copy_range__not_same),\
    UT_CASE(test_list_init_copy_range__init_copy_range_empty),\
    UT_CASE(test_list_init_copy_range__c_builtin),\
    UT_CASE(test_list_init_copy_range__cstr),\
    UT_CASE(test_list_init_copy_range__libcstl_builtin),\
    UT_CASE(test_list_init_copy_range__user_define),\
    UT_CASE(test_list_init_copy_range__other_container_range),\
    UT_CASE(test_list_init_copy_range__other_container_range1),\
    UT_CASE_BEGIN(list_init_copy_array, test_list_init_copy_array__null_list_container),\
    UT_CASE(test_list_init_copy_array__non_created_list_container),\
    UT_CASE(test_list_init_copy_array__invalid_array),\
    UT_CASE(test_list_init_copy_array__init_copy_array_empty),\
    UT_CASE(test_list_init_copy_array__c_builtin),\
    UT_CASE(test_list_init_copy_array__cstr),\
    UT_CASE(test_list_init_copy_array__libcstl_builtin),\
    UT_CASE(test_list_init_copy_array__user_define),\
    UT_CASE_BEGIN(list_size, test_list_size__null_list_container),\
    UT_CASE(test_list_size__non_inited_list_container),\
    UT_CASE(test_list_size__empty),\
    UT_CASE(test_list_size__non_empty),\
    UT_CASE_BEGIN(list_empty, test_list_empty__null_list_container),\
    UT_CASE(test_list_empty__non_inited_list_container),\
    UT_CASE(test_list_empty__empty),\
    UT_CASE(test_list_empty__non_empty),\
    UT_CASE_BEGIN(list_max_size, test_list_max_size__null_list_container),\
    UT_CASE(test_list_max_size__non_inited_list_container),\
    UT_CASE(test_list_max_size__empty),\
    UT_CASE(test_list_max_size__non_empty),\
    UT_CASE_BEGIN(list_equal, test_list_equal__null_first),\
    UT_CASE(test_list_equal__null_second),\
    UT_CASE(test_list_equal__non_inited_first),\
    UT_CASE(test_list_equal__non_inited_second),\
    UT_CASE(test_list_equal__not_same_type),\
    UT_CASE(test_list_equal__same_list),\
    UT_CASE(test_list_equal__size_first_less_than_second),\
    UT_CASE(test_list_equal__size_first_greater_than_second),\
    UT_CASE(test_list_equal__size_equal_0),\
    UT_CASE(test_list_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_not_equal, test_list_not_equal__null_first),\
    UT_CASE(test_list_not_equal__null_second),\
    UT_CASE(test_list_not_equal__non_inited_first),\
    UT_CASE(test_list_not_equal__non_inited_second),\
    UT_CASE(test_list_not_equal__not_same_type),\
    UT_CASE(test_list_not_equal__same_list),\
    UT_CASE(test_list_not_equal__size_first_less_than_second),\
    UT_CASE(test_list_not_equal__size_first_greater_than_second),\
    UT_CASE(test_list_not_equal__size_equal_0),\
    UT_CASE(test_list_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_less, test_list_less__null_first),\
    UT_CASE(test_list_less__null_second),\
    UT_CASE(test_list_less__non_inited_first),\
    UT_CASE(test_list_less__non_inited_second),\
    UT_CASE(test_list_less__not_same_type),\
    UT_CASE(test_list_less__same_list),\
    UT_CASE(test_list_less__size_first_less_than_second),\
    UT_CASE(test_list_less__size_first_greater_than_second),\
    UT_CASE(test_list_less__size_equal_0),\
    UT_CASE(test_list_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_less_equal, test_list_less_equal__null_first),\
    UT_CASE(test_list_less_equal__null_second),\
    UT_CASE(test_list_less_equal__non_inited_first),\
    UT_CASE(test_list_less_equal__non_inited_second),\
    UT_CASE(test_list_less_equal__not_same_type),\
    UT_CASE(test_list_less_equal__same_list),\
    UT_CASE(test_list_less_equal__size_first_less_than_second),\
    UT_CASE(test_list_less_equal__size_first_greater_than_second),\
    UT_CASE(test_list_less_equal__size_equal_0),\
    UT_CASE(test_list_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_greater, test_list_greater__null_first),\
    UT_CASE(test_list_greater__null_second),\
    UT_CASE(test_list_greater__non_inited_first),\
    UT_CASE(test_list_greater__non_inited_second),\
    UT_CASE(test_list_greater__not_same_type),\
    UT_CASE(test_list_greater__same_list),\
    UT_CASE(test_list_greater__size_first_less_than_second),\
    UT_CASE(test_list_greater__size_first_greater_than_second),\
    UT_CASE(test_list_greater__size_equal_0),\
    UT_CASE(test_list_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_greater_equal, test_list_greater_equal__null_first),\
    UT_CASE(test_list_greater_equal__null_second),\
    UT_CASE(test_list_greater_equal__non_inited_first),\
    UT_CASE(test_list_greater_equal__non_inited_second),\
    UT_CASE(test_list_greater_equal__not_same_type),\
    UT_CASE(test_list_greater_equal__same_list),\
    UT_CASE(test_list_greater_equal__size_first_less_than_second),\
    UT_CASE(test_list_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_list_greater_equal__size_equal_0),\
    UT_CASE(test_list_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_list_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_list_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(list_assign, test_list_assign__null_dest),\
    UT_CASE(test_list_assign__null_src),\
    UT_CASE(test_list_assign__non_inited_dest),\
    UT_CASE(test_list_assign__non_inited_src),\
    UT_CASE(test_list_assign__not_same_type),\
    UT_CASE(test_list_assign__same_container),\
    UT_CASE(test_list_assign__0_assign_0),\
    UT_CASE(test_list_assign__0_assign_10),\
    UT_CASE(test_list_assign__10_assign_0),\
    UT_CASE(test_list_assign__10_assign_10_list_equal),\
    UT_CASE(test_list_assign__10_assign_10_list_not_equal),\
    UT_CASE(test_list_assign__10_assign_1000),\
    UT_CASE_BEGIN(list_assign_range, test_list_assign_range__null_list_container),\
    UT_CASE(test_list_assign_range__non_inited),\
    UT_CASE(test_list_assign_range__invalid_it_begin),\
    UT_CASE(test_list_assign_range__invalid_it_end),\
    UT_CASE(test_list_assign_range__invalid_range),\
    UT_CASE(test_list_assign_range__invalid_range_not_same_type),\
    UT_CASE(test_list_assign_range__range_belong_to_list),\
    UT_CASE(test_list_assign_range__0_assign_range_0),\
    UT_CASE(test_list_assign_range__0_assign_range_10),\
    UT_CASE(test_list_assign_range__10_assign_range_0),\
    UT_CASE(test_list_assign_range__10_assign_range_10_same_elem),\
    UT_CASE(test_list_assign_range__10_assign_range_10_not_same_elem),\
    UT_CASE(test_list_assign_range__10_assign_range_1000),\
    UT_CASE(test_list_assign_range__other_container_range),\
    UT_CASE_BEGIN(list_assign_array, test_list_assign_array__null_list_container),\
    UT_CASE(test_list_assign_array__non_inited),\
    UT_CASE(test_list_assign_array__invalid_array),\
    UT_CASE(test_list_assign_array__0_assign_array_0),\
    UT_CASE(test_list_assign_array__0_assign_array_10),\
    UT_CASE(test_list_assign_array__10_assign_array_0),\
    UT_CASE(test_list_assign_array__10_assign_array_10_same_elem),\
    UT_CASE(test_list_assign_array__10_assign_array_10_not_same_elem),\
    UT_CASE(test_list_assign_array__10_assign_array_1000),\
    UT_CASE(test_list_assign_array__cstr),\
    UT_CASE(test_list_assign_array__user_define),\
    UT_CASE(test_list_assign_array__cstl_builtin),\
    UT_CASE_BEGIN(list_swap, test_list_swap__null_first),\
    UT_CASE(test_list_swap__null_second),\
    UT_CASE(test_list_swap__non_inited_first),\
    UT_CASE(test_list_swap__non_inited_second),\
    UT_CASE(test_list_swap__not_same_type),\
    UT_CASE(test_list_swap__list_equal),\
    UT_CASE(test_list_swap__0_swap_10),\
    UT_CASE(test_list_swap__10_swap_0),\
    UT_CASE(test_list_swap__10_swap_10),\
    UT_CASE(test_list_swap__10_swap_1000),\
    UT_CASE_BEGIN(list_front, test_list_front__null_list_container),\
    UT_CASE(test_list_front__non_inited_list_container),\
    UT_CASE(test_list_front__empty),\
    UT_CASE(test_list_front__successfully),\
    UT_CASE(test_list_front__successfully_cstr),\
    UT_CASE_BEGIN(list_back, test_list_back__null_list_container),\
    UT_CASE(test_list_back__non_inited_list_container),\
    UT_CASE(test_list_back__empty),\
    UT_CASE(test_list_back__successfully),\
    UT_CASE(test_list_back__successfully_cstr),\
    UT_CASE_BEGIN(list_begin, test_list_begin__null_list_container),\
    UT_CASE(test_list_begin__non_inited_list_container),\
    UT_CASE(test_list_begin__empty),\
    UT_CASE(test_list_begin__non_empty),\
    UT_CASE_BEGIN(list_end, test_list_end__null_list_container),\
    UT_CASE(test_list_end__non_inited_list_container),\
    UT_CASE(test_list_end__empty),\
    UT_CASE(test_list_end__non_empty),\
    UT_CASE_BEGIN(list_insert_range, test_list_insert_range__null_list_container),\
    UT_CASE(test_list_insert_range__non_inited),\
    UT_CASE(test_list_insert_range__invalid_position),\
    UT_CASE(test_list_insert_range__invalid_range),\
    UT_CASE(test_list_insert_range__invalid_range_not_same_type),\
    UT_CASE(test_list_insert_range__invalid_range_belong_to_list),\
    UT_CASE(test_list_insert_range__empty_insert_0),\
    UT_CASE(test_list_insert_range__empty_insert_10),\
    UT_CASE(test_list_insert_range__begin_insert_0),\
    UT_CASE(test_list_insert_range__begin_insert_10),\
    UT_CASE(test_list_insert_range__middle_insert_0),\
    UT_CASE(test_list_insert_range__middle_insert_10),\
    UT_CASE(test_list_insert_range__end_insert_0),\
    UT_CASE(test_list_insert_range__end_insert_10),\
    UT_CASE(test_list_insert_range__other_container_range),\
    UT_CASE_BEGIN(list_insert_array, test_list_insert_array__null_list_container),\
    UT_CASE(test_list_insert_array__non_inited),\
    UT_CASE(test_list_insert_array__invalid_position),\
    UT_CASE(test_list_insert_array__invalid_array),\
    UT_CASE(test_list_insert_array__empty_insert_0),\
    UT_CASE(test_list_insert_array__empty_insert_10),\
    UT_CASE(test_list_insert_array__begin_insert_0),\
    UT_CASE(test_list_insert_array__begin_insert_10),\
    UT_CASE(test_list_insert_array__middle_insert_0),\
    UT_CASE(test_list_insert_array__middle_insert_10),\
    UT_CASE(test_list_insert_array__end_insert_0),\
    UT_CASE(test_list_insert_array__end_insert_10),\
    UT_CASE(test_list_insert_array__cstr),\
    UT_CASE(test_list_insert_array__cstl),\
    UT_CASE(test_list_insert_array__user_define),\
    UT_CASE_BEGIN(list_pop_back, test_list_pop_back__null_list_container),\
    UT_CASE(test_list_pop_back__non_inited_list_container),\
    UT_CASE(test_list_pop_back__empty),\
    UT_CASE(test_list_pop_back__successfully),\
    UT_CASE_BEGIN(list_pop_front, test_list_pop_front__null_list_container),\
    UT_CASE(test_list_pop_front__non_inited_list_container),\
    UT_CASE(test_list_pop_front__empty),\
    UT_CASE(test_list_pop_front__successfully),\
    UT_CASE_BEGIN(list_erase, test_list_erase__null_list_container),\
    UT_CASE(test_list_erase__non_inited_list_container),\
    UT_CASE(test_list_erase__invalid_pos_end),\
    UT_CASE(test_list_erase__invalid_pos),\
    UT_CASE(test_list_erase__successfully_begin),\
    UT_CASE(test_list_erase__successfully_middle),\
    UT_CASE(test_list_erase__successfully_back),\
    UT_CASE_BEGIN(list_erase_range, test_list_erase_range__null_list_container),\
    UT_CASE(test_list_erase_range__non_inited_list_container),\
    UT_CASE(test_list_erase_range__invalid_range_not_belong_to_list),\
    UT_CASE(test_list_erase_range__invalid_range),\
    UT_CASE(test_list_erase_range__successfully_empty),\
    UT_CASE(test_list_erase_range__successfully_begin),\
    UT_CASE(test_list_erase_range__successfully_middle),\
    UT_CASE(test_list_erase_range__successfully_end),\
    UT_CASE(test_list_erase_range__successfully_all),\
    UT_CASE_BEGIN(list_remove_if, test_list_remove_if__null_list_container),\
    UT_CASE(test_list_remove_if__non_inited_list_container),\
    UT_CASE(test_list_remove_if__empty),\
    UT_CASE(test_list_remove_if__non_empty_no_removed),\
    UT_CASE(test_list_remove_if__non_empty_remove),\
    UT_CASE(test_list_remove_if__non_empty_remove_more),\
    UT_CASE(test_list_remove_if__non_empty_remove_all),\
    UT_CASE(test_list_remove_if__empty_default_ufun_op),\
    UT_CASE(test_list_remove_if__non_empty_default_ufun_op),\
    UT_CASE(test_list_remove_if__cstr_empty),\
    UT_CASE(test_list_remove_if__cstr_non_empty_no_removed),\
    UT_CASE(test_list_remove_if__cstr_non_empty_remove),\
    UT_CASE(test_list_remove_if__cstr_non_empty_remove_more),\
    UT_CASE(test_list_remove_if__cstr_non_empty_remove_all),\
    UT_CASE_BEGIN(list_resize, test_list_resize__null_list_container),\
    UT_CASE(test_list_resize__non_inited),\
    UT_CASE(test_list_resize__successfully_0_resize_0),\
    UT_CASE(test_list_resize__successfully_0_resize_10),\
    UT_CASE(test_list_resize__successfully_10_resize_0),\
    UT_CASE(test_list_resize__successfully_10_resize_10),\
    UT_CASE(test_list_resize__successfully_10_resize_1000),\
    UT_CASE_BEGIN(list_clear, test_list_clear__null_list_container),\
    UT_CASE(test_list_clear__non_inited_list_container),\
    UT_CASE(test_list_clear__empty_list_container),\
    UT_CASE(test_list_clear__non_empty_list_container),\
    UT_CASE_BEGIN(list_unique, test_list_unique__null_list_container),\
    UT_CASE(test_list_unique__non_inited_list_container),\
    UT_CASE(test_list_unique__empty),\
    UT_CASE(test_list_unique__non_empty_no_duplicate),\
    UT_CASE(test_list_unique__non_empty_adjacent_duplicate),\
    UT_CASE(test_list_unique__non_empty_not_adjacent_duplicate),\
    UT_CASE(test_list_unique__non_empty_all_duplicate),\
    UT_CASE(test_list_unique__cstr_non_empty_no_duplicate),\
    UT_CASE(test_list_unique__cstr_non_empty_adjacent_duplicate),\
    UT_CASE(test_list_unique__cstr_non_empty_not_adjacent_duplicate),\
    UT_CASE(test_list_unique__cstr_non_empty_all_duplicate),\
    UT_CASE_BEGIN(list_unique_if, test_list_unique_if__null_list_container),\
    UT_CASE(test_list_unique_if__non_inited_list_container),\
    UT_CASE(test_list_unique_if__empty),\
    UT_CASE(test_list_unique_if__non_empty_non_duplicate),\
    UT_CASE(test_list_unique_if__non_empty_duplicate),\
    UT_CASE(test_list_unique_if__non_empty_more_duplicate),\
    UT_CASE(test_list_unique_if__non_empty_duplicate_not_adjacent),\
    UT_CASE(test_list_unique_if__non_empty_duplicate_all),\
    UT_CASE(test_list_unique_if__cstr_non_empty_no_duplicate),\
    UT_CASE(test_list_unique_if__cstr_non_empty_adjacent_duplicate),\
    UT_CASE(test_list_unique_if__cstr_non_empty_not_adjacent_duplicate),\
    UT_CASE(test_list_unique_if__cstr_non_empty_all_duplicate),\
    UT_CASE(test_list_unique_if__default_predicate),\
    UT_CASE_BEGIN(list_splice, test_list_splice__null_target_list_container),\
    UT_CASE(test_list_splice__null_source_list_container),\
    UT_CASE(test_list_splice__non_inited_target_list_container),\
    UT_CASE(test_list_splice__non_inited_source_list_container),\
    UT_CASE(test_list_splice__not_same_type),\
    UT_CASE(test_list_splice__invalid_target_position),\
    UT_CASE(test_list_splice__same_list),\
    UT_CASE(test_list_splice__target_empty_source_empty),\
    UT_CASE(test_list_splice__target_empty_source_non_empty),\
    UT_CASE(test_list_splice__target_begin_source_empty),\
    UT_CASE(test_list_splice__target_begin_source_non_empty),\
    UT_CASE(test_list_splice__target_middle_source_non_empty),\
    UT_CASE(test_list_splice__target_end_source_non_empty),\
    UT_CASE_BEGIN(list_splice_pos, test_list_splice_pos__null_target_list_container),\
    UT_CASE(test_list_splice_pos__null_source_list_container),\
    UT_CASE(test_list_splice_pos__non_inited_target_list_container),\
    UT_CASE(test_list_splice_pos__non_inited_source_list_container),\
    UT_CASE(test_list_splice_pos__not_same),\
    UT_CASE(test_list_splice_pos__invalid_tearget_position),\
    UT_CASE(test_list_splice_pos__invalid_source_position),\
    UT_CASE(test_list_splice_pos__invalid_source_position_end),\
    UT_CASE(test_list_splice_pos__same_list_container_same_position),\
    UT_CASE(test_list_splice_pos__same_list_container_next_position),\
    UT_CASE(test_list_splice_pos__same_list_container_not_same_not_next_position),\
    UT_CASE(test_list_splice_pos__target_empty),\
    UT_CASE(test_list_splice_pos__target_begin_source_begin),\
    UT_CASE(test_list_splice_pos__target_middle_source_middle),\
    UT_CASE(test_list_splice_pos__target_end_source_begin),\
    UT_CASE_BEGIN(list_splice_range, test_list_splice_range__null_target_list_container),\
    UT_CASE(test_list_splice_range__null_source_list_container),\
    UT_CASE(test_list_splice_range__non_inited_target_list_container),\
    UT_CASE(test_list_splice_range__non_inited_source_list_container),\
    UT_CASE(test_list_splice_range__not_same),\
    UT_CASE(test_list_splice_range__invalid_tearget_position),\
    UT_CASE(test_list_splice_range__invalid_source_range),\
    UT_CASE(test_list_splice_range__invalid_target_position_in_range),\
    UT_CASE(test_list_splice_range__same_list_container_pos_equal_begin),\
    UT_CASE(test_list_splice_range__same_list_container_pos_equal_end),\
    UT_CASE(test_list_splice_range__same_list_container_pos_not_in_range),\
    UT_CASE(test_list_splice_range__target_empty_range_empty),\
    UT_CASE(test_list_splice_range__target_empty_range_not_empty),\
    UT_CASE(test_list_splice_range__target_begin_source_begin),\
    UT_CASE(test_list_splice_range__target_middle_source_middle),\
    UT_CASE(test_list_splice_range__target_end_source_all),\
    UT_CASE_BEGIN(list_sort, test_list_sort__null_list_container),\
    UT_CASE(test_list_sort__non_inited_list_container),\
    UT_CASE(test_list_sort__empty_less),\
    UT_CASE(test_list_sort__1_less),\
    UT_CASE(test_list_sort__2_equal_less),\
    UT_CASE(test_list_sort__2_less_less),\
    UT_CASE(test_list_sort__2_greater_less),\
    UT_CASE(test_list_sort__random_equal_less),\
    UT_CASE(test_list_sort__random_less_less),\
    UT_CASE(test_list_sort__random_greater_less),\
    UT_CASE(test_list_sort__random_random_less),\
    UT_CASE(test_list_sort__random_random_dup_less),\
    UT_CASE_BEGIN(list_sort_if, test_list_sort_if__null_list_container),\
    UT_CASE(test_list_sort_if__non_inited_list_container),\
    UT_CASE(test_list_sort_if__empty_less),\
    UT_CASE(test_list_sort_if__empty_greater),\
    UT_CASE(test_list_sort_if__1_less),\
    UT_CASE(test_list_sort_if__1_greater),\
    UT_CASE(test_list_sort_if__2_equal_less),\
    UT_CASE(test_list_sort_if__2_equal_greater),\
    UT_CASE(test_list_sort_if__2_less_less),\
    UT_CASE(test_list_sort_if__2_less_greater),\
    UT_CASE(test_list_sort_if__2_greater_less),\
    UT_CASE(test_list_sort_if__2_greater_greater),\
    UT_CASE(test_list_sort_if__random_equal_less),\
    UT_CASE(test_list_sort_if__random_equal_greater),\
    UT_CASE(test_list_sort_if__random_less_less),\
    UT_CASE(test_list_sort_if__random_less_greater),\
    UT_CASE(test_list_sort_if__random_greater_less),\
    UT_CASE(test_list_sort_if__random_greater_greater),\
    UT_CASE(test_list_sort_if__random_random_less),\
    UT_CASE(test_list_sort_if__random_random_greater),\
    UT_CASE(test_list_sort_if__random_random_dup_less),\
    UT_CASE(test_list_sort_if__random_random_dup_greater),\
    UT_CASE(test_list_sort_if__cstr_1_less),\
    UT_CASE(test_list_sort_if__cstr_1_greater),\
    UT_CASE(test_list_sort_if__cstr_2_equal_less),\
    UT_CASE(test_list_sort_if__cstr_2_equal_greater),\
    UT_CASE(test_list_sort_if__cstr_2_less_less),\
    UT_CASE(test_list_sort_if__cstr_2_less_greater),\
    UT_CASE(test_list_sort_if__cstr_2_greater_less),\
    UT_CASE(test_list_sort_if__cstr_2_greater_greater),\
    UT_CASE(test_list_sort_if__cstr_random_equal_less),\
    UT_CASE(test_list_sort_if__cstr_random_equal_greater),\
    UT_CASE(test_list_sort_if__cstr_random_less_less),\
    UT_CASE(test_list_sort_if__cstr_random_less_greater),\
    UT_CASE(test_list_sort_if__cstr_random_greater_less),\
    UT_CASE(test_list_sort_if__cstr_random_greater_greater),\
    UT_CASE(test_list_sort_if__cstr_random_random_less),\
    UT_CASE(test_list_sort_if__cstr_random_random_greater),\
    UT_CASE(test_list_sort_if__cstr_random_random_dup_less),\
    UT_CASE(test_list_sort_if__cstr_random_random_dup_greater),\
    UT_CASE_BEGIN(list_merge, test_list_merge__null_dest_list_container),\
    UT_CASE(test_list_merge__null_src_list_container),\
    UT_CASE(test_list_merge__non_inited_dest_list_container),\
    UT_CASE(test_list_merge__non_inited_src_list_container),\
    UT_CASE(test_list_merge__not_same),\
    UT_CASE(test_list_merge__same_list_container),\
    UT_CASE(test_list_merge__dest_empty_src_empty),\
    UT_CASE(test_list_merge__dest_non_empty_src_empty),\
    UT_CASE(test_list_merge__dest_empty_src_non_empty),\
    UT_CASE(test_list_merge__dest_tailing),\
    UT_CASE(test_list_merge__src_tailing),\
    UT_CASE(test_list_merge__random),\
    UT_CASE(test_list_merge__cstr_dest_tailing),\
    UT_CASE(test_list_merge__cstr_src_tailing),\
    UT_CASE(test_list_merge__cstr_random),\
    UT_CASE_BEGIN(list_merge_if, test_list_merge_if__null_dest_list_container),\
    UT_CASE(test_list_merge_if__null_src_list_container),\
    UT_CASE(test_list_merge_if__non_inited_dest_list_container),\
    UT_CASE(test_list_merge_if__non_inited_src_list_container),\
    UT_CASE(test_list_merge_if__not_same),\
    UT_CASE(test_list_merge_if__same_list_container),\
    UT_CASE(test_list_merge_if__dest_empty_src_empty),\
    UT_CASE(test_list_merge_if__dest_non_empty_src_empty),\
    UT_CASE(test_list_merge_if__dest_empty_src_non_empty),\
    UT_CASE(test_list_merge_if__ascending_dest_tailing),\
    UT_CASE(test_list_merge_if__ascending_src_tailing),\
    UT_CASE(test_list_merge_if__descending_dest_tailing),\
    UT_CASE(test_list_merge_if__descending_src_tailing),\
    UT_CASE(test_list_merge_if__random),\
    UT_CASE(test_list_merge_if__cstr_ascending_dest_tailing),\
    UT_CASE(test_list_merge_if__cstr_ascending_src_tailing),\
    UT_CASE(test_list_merge_if__cstr_descending_dest_tailing),\
    UT_CASE(test_list_merge_if__cstr_descending_src_tailing),\
    UT_CASE(test_list_merge_if__cstr_random),\
    UT_CASE_BEGIN(list_reverse, test_list_reverse__null_list_container),\
    UT_CASE(test_list_reverse__non_inited_list_container),\
    UT_CASE(test_list_reverse__empty),\
    UT_CASE(test_list_reverse__same),\
    UT_CASE(test_list_reverse__not_same)

#endif /* _UT_CSTL_LIST_H_ */

