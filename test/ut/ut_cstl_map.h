#ifndef _UT_CSTL_MAP_H_
#define _UT_CSTL_MAP_H_

UT_SUIT_DECLARATION(cstl_map)
/*
 * test map_init
 */
UT_CASE_DECLARATION(map_init)
void test_map_init__null_map(void** state);
void test_map_init__non_created(void** state);
void test_map_init__non_created_pair(void** state);
void test_map_init__null_compare(void** state);
/*
 * test map_init_ex
 */
UT_CASE_DECLARATION(map_init_ex)
void test_map_init_ex__null_map(void** state);
void test_map_init_ex__non_created(void** state);
void test_map_init_ex__non_created_pair(void** state);
void test_map_init_ex__null_compare(void** state);
void test_map_init_ex__non_null_compare(void** state);
/*
 * test map_init_copy
 */
UT_CASE_DECLARATION(map_init_copy)
void test_map_init_copy__null_dest(void** state);
void test_map_init_copy__null_src(void** state);
void test_map_init_copy__non_created_dest(void** state);
void test_map_init_copy__non_created_dest_pair(void** state);
void test_map_init_copy__non_inited_src(void** state);
void test_map_init_copy__non_inited_src_pair(void** state);
void test_map_init_copy__not_same_type(void** state);
void test_map_init_copy__empty(void** state);
void test_map_init_copy__non_empty(void** state);
void test_map_init_copy__non_null_compare(void** state);
/*
 * test map_init_copy_range
 */
UT_CASE_DECLARATION(map_init_copy_range)
void test_map_init_copy_range__null_map(void** state);
void test_map_init_copy_range__non_created_map(void** state);
void test_map_init_copy_range__non_created_map_pair(void** state);
void test_map_init_copy_range__invalid_begin(void** state);
void test_map_init_copy_range__invalid_end(void** state);
void test_map_init_copy_range__invalid_range(void** state);
void test_map_init_copy_range__invalid_range_not_same_type(void** state);
void test_map_init_copy_range__empty(void** state);
void test_map_init_copy_range__non_empty(void** state);
void test_map_init_copy_range__other_container_range(void** state);
void test_map_init_copy_range__other_container_range_dup(void** state);
void test_map_init_copy_range__other_container_range_not_same_type(void** state);
/*void test_map_init_copy_range__other_container_range_not_pair(void** state);*/
/*
 * test map_init_copy_array
 */
UT_CASE_DECLARATION(map_init_copy_array)
void test_map_init_copy_array__null_map(void** state);
void test_map_init_copy_array__non_created_map(void** state);
void test_map_init_copy_array__non_created_map_pair(void** state);
void test_map_init_copy_array__invalid_array(void** state);
void test_map_init_copy_array__invalid_array_not_same_type(void** state);
void test_map_init_copy_array__empty(void** state);
void test_map_init_copy_array__non_empty(void** state);
void test_map_init_copy_array__non_empty_dup(void** state);
/*void test_map_init_copy_array__array_not_pair(void** state);*/
/*
 * test map_init_copy_range_ex
 */
UT_CASE_DECLARATION(map_init_copy_range_ex)
void test_map_init_copy_range_ex__null_map(void** state);
void test_map_init_copy_range_ex__non_created_map(void** state);
void test_map_init_copy_range_ex__non_created_map_pair(void** state);
void test_map_init_copy_range_ex__invalid_begin(void** state);
void test_map_init_copy_range_ex__invalid_end(void** state);
void test_map_init_copy_range_ex__invalid_range(void** state);
void test_map_init_copy_range_ex__invalid_range_not_same_type(void** state);
void test_map_init_copy_range_ex__empty(void** state);
void test_map_init_copy_range_ex__non_empty(void** state);
void test_map_init_copy_range_ex__compare(void** state);
void test_map_init_copy_range_ex__other_container_range(void** state);
void test_map_init_copy_range_ex__other_container_range_dup(void** state);
void test_map_init_copy_range_ex__other_container_range_not_same_type(void** state);
/*void test_map_init_copy_range_ex__other_container_range_not_pair(void** state);*/
/*
 * test map_init_copy_array_ex
 */
UT_CASE_DECLARATION(map_init_copy_array_ex)
void test_map_init_copy_array_ex__null_map(void** state);
void test_map_init_copy_array_ex__non_created_map(void** state);
void test_map_init_copy_array_ex__non_created_map_pair(void** state);
void test_map_init_copy_array_ex__invalid_array(void** state);
void test_map_init_copy_array_ex__invalid_array_not_same_type(void** state);
void test_map_init_copy_array_ex__empty(void** state);
void test_map_init_copy_array_ex__non_empty(void** state);
void test_map_init_copy_array_ex__non_empty_dup(void** state);
void test_map_init_copy_array_ex__compare(void** state);
/*void test_map_init_copy_array_ex__array_not_pair(void** state);*/
/*
 * test map_destroy
 */
UT_CASE_DECLARATION(map_destroy)
void test_map_destroy__null_map(void** state);
void test_map_destroy__non_created(void** state);
void test_map_destroy__created(void** state);
void test_map_destroy__inited(void** state);
void test_map_destroy__non_empty(void** state);
/*
 * test map_assign
 */
UT_CASE_DECLARATION(map_assign)
void test_map_assign__null_dest(void** state);
void test_map_assign__null_src(void** state);
void test_map_assign__non_created_dest(void** state);
void test_map_assign__non_created_dest_pair(void** state);
void test_map_assign__non_init_src(void** state);
void test_map_assign__non_init_src_pair(void** state);
void test_map_assign__not_same_type(void** state);
void test_map_assign__empty_empty(void** state);
void test_map_assign__non_empty_empty(void** state);
void test_map_assign__non_empty_non_empty_less(void** state);
void test_map_assign__non_empty_non_empty_size_equal(void** state);
void test_map_assign__non_empty_non_empty_equal(void** state);
void test_map_assign__non_empty_non_empty_greater(void** state);
void test_map_assign__empty_non_empty(void** state);
/*
 * test map_size
 */
UT_CASE_DECLARATION(map_size)
void test_map_size__null_map(void** state);
void test_map_size__non_inited(void** state);
void test_map_size__non_inited_pair(void** state);
void test_map_size__empty(void** state);
void test_map_size__non_empty(void** state);
/*
 * test _map_emtpy
 */
UT_CASE_DECLARATION(map_empty)
void test_map_empty__null_map(void** state);
void test_map_empty__non_inited(void** state);
void test_map_empty__non_inited_pair(void** state);
void test_map_empty__empty(void** state);
void test_map_empty__non_empty(void** state);
/*
 * test map_max_size
 */
UT_CASE_DECLARATION(map_max_size)
void test_map_max_size__null_map(void** state);
void test_map_max_size__non_inited(void** state);
void test_map_max_size__non_inited_pair(void** state);
void test_map_max_size__empty(void** state);
void test_map_max_size__non_empty(void** state);
/*
 * test map_begin
 */
UT_CASE_DECLARATION(map_begin)
void test_map_begin__null_map(void** state);
void test_map_begin__non_inited(void** state);
void test_map_begin__non_inited_pair(void** state);
void test_map_begin__empty(void** state);
void test_map_begin__non_empty(void** state);
/*
 * test map_end
 */
UT_CASE_DECLARATION(map_end)
void test_map_end__null_map(void** state);
void test_map_end__non_inited(void** state);
void test_map_end__non_inited_pair(void** state);
void test_map_end__empty(void** state);
void test_map_end__non_empty(void** state);
/*
 * test map_key_comp
 */
UT_CASE_DECLARATION(map_key_comp)
void test_map_key_comp__null_map(void** state);
void test_map_key_comp__non_inited(void** state);
void test_map_key_comp__default_key_comp(void** state);
void test_map_key_comp__user_define_key_comp(void** state);
/*
 * test map_value_comp
 */
UT_CASE_DECLARATION(map_value_comp)
void test_map_value_comp__null_map(void** state);
void test_map_value_comp__non_inited(void** state);
void test_map_value_comp__default_value_comp(void** state);
void test_map_value_comp__user_define_value_comp(void** state);
/*
 * test map_clear
 */
UT_CASE_DECLARATION(map_clear)
void test_map_clear__null_map(void** state);
void test_map_clear__non_inited(void** state);
void test_map_clear__non_inited_pair(void** state);
void test_map_clear__empty(void** state);
void test_map_clear__non_empty(void** state);
/*
 * test map_equal
 */
UT_CASE_DECLARATION(map_equal)
void test_map_equal__null_first(void** state);
void test_map_equal__null_second(void** state);
void test_map_equal__non_inited_first(void** state);
void test_map_equal__non_inited_first_pair(void** state);
void test_map_equal__non_inited_second(void** state);
void test_map_equal__non_inited_second_pair(void** state);
void test_map_equal__not_same_type(void** state);
void test_map_equal__same_map(void** state);
void test_map_equal__size_first_less_than_second(void** state);
void test_map_equal__size_first_greater_than_second(void** state);
void test_map_equal__size_equal_0(void** state);
void test_map_equal__size_equal_elem_first_less_than_second(void** state);
void test_map_equal__size_equal_elem_first_greater_than_second(void** state);
void test_map_equal__compare_not_equal(void** state);
void test_map_equal__equal(void** state);
/*
 * test map_not_equal
 */
UT_CASE_DECLARATION(map_not_equal)
void test_map_not_equal__null_first(void** state);
void test_map_not_equal__null_second(void** state);
void test_map_not_equal__non_inited_first(void** state);
void test_map_not_equal__non_inited_first_pair(void** state);
void test_map_not_equal__non_inited_second(void** state);
void test_map_not_equal__non_inited_second_pair(void** state);
void test_map_not_equal__not_same_type(void** state);
void test_map_not_equal__same_map(void** state);
void test_map_not_equal__size_first_less_than_second(void** state);
void test_map_not_equal__size_first_greater_than_second(void** state);
void test_map_not_equal__size_equal_0(void** state);
void test_map_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_map_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_map_not_equal__compare_not_equal(void** state);
void test_map_not_equal__equal(void** state);
/*
 * test map_less
 */
UT_CASE_DECLARATION(map_less)
void test_map_less__null_first(void** state);
void test_map_less__null_second(void** state);
void test_map_less__non_inited_first(void** state);
void test_map_less__non_inited_first_pair(void** state);
void test_map_less__non_inited_second(void** state);
void test_map_less__non_inited_second_pair(void** state);
void test_map_less__not_same_type(void** state);
void test_map_less__same_map(void** state);
void test_map_less__size_first_less_than_second(void** state);
void test_map_less__size_first_greater_than_second(void** state);
void test_map_less__size_equal_0(void** state);
void test_map_less__size_equal_elem_first_less_than_second(void** state);
void test_map_less__size_equal_elem_first_greater_than_second(void** state);
void test_map_less__compare_less(void** state);
void test_map_less__equal(void** state);
/*
 * test map_less_equal
 */
UT_CASE_DECLARATION(map_less_equal)
void test_map_less_equal__null_first(void** state);
void test_map_less_equal__null_second(void** state);
void test_map_less_equal__non_inited_first(void** state);
void test_map_less_equal__non_inited_first_pair(void** state);
void test_map_less_equal__non_inited_second(void** state);
void test_map_less_equal__non_inited_second_pair(void** state);
void test_map_less_equal__not_same_type(void** state);
void test_map_less_equal__same_map(void** state);
void test_map_less_equal__size_first_less_than_second(void** state);
void test_map_less_equal__size_first_greater_than_second(void** state);
void test_map_less_equal__size_equal_0(void** state);
void test_map_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_map_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_map_less_equal__compare_less(void** state);
void test_map_less_equal__equal(void** state);
/*
 * test map_greater
 */
UT_CASE_DECLARATION(map_greater)
void test_map_greater__null_first(void** state);
void test_map_greater__null_second(void** state);
void test_map_greater__non_inited_first(void** state);
void test_map_greater__non_inited_first_pair(void** state);
void test_map_greater__non_inited_second(void** state);
void test_map_greater__non_inited_second_pair(void** state);
void test_map_greater__not_same_type(void** state);
void test_map_greater__same_map(void** state);
void test_map_greater__size_first_less_than_second(void** state);
void test_map_greater__size_first_greater_than_second(void** state);
void test_map_greater__size_equal_0(void** state);
void test_map_greater__size_equal_elem_first_less_than_second(void** state);
void test_map_greater__size_equal_elem_first_greater_than_second(void** state);
void test_map_greater__compare_less(void** state);
void test_map_greater__equal(void** state);
/*
 * test map_greater_equal
 */
UT_CASE_DECLARATION(map_greater_equal)
void test_map_greater_equal__null_first(void** state);
void test_map_greater_equal__null_second(void** state);
void test_map_greater_equal__non_inited_first(void** state);
void test_map_greater_equal__non_inited_first_pair(void** state);
void test_map_greater_equal__non_inited_second(void** state);
void test_map_greater_equal__non_inited_second_pair(void** state);
void test_map_greater_equal__not_same_type(void** state);
void test_map_greater_equal__same_map(void** state);
void test_map_greater_equal__size_first_less_than_second(void** state);
void test_map_greater_equal__size_first_greater_than_second(void** state);
void test_map_greater_equal__size_equal_0(void** state);
void test_map_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_map_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_map_greater_equal__compare_less(void** state);
void test_map_greater_equal__equal(void** state);
/*
 * test map_swap
 */
UT_CASE_DECLARATION(map_swap)
void test_map_swap__null_first(void** state);
void test_map_swap__null_second(void** state);
void test_map_swap__non_inited_first(void** state);
void test_map_swap__non_inited_first_pair(void** state);
void test_map_swap__non_inited_second(void** state);
void test_map_swap__non_inited_second_pair(void** state);
void test_map_swap__not_same_type(void** state);
void test_map_swap__same_map(void** state);
void test_map_swap__0_swap_n(void** state);
void test_map_swap__n_swap_0(void** state);
void test_map_swap__n_swap_n(void** state);
void test_map_swap__m_swap_n(void** state);
/*
 * test map_insert
 */
UT_CASE_DECLARATION(map_insert)
void test_map_insert__null_map(void** state);
void test_map_insert__null_pair(void** state);
void test_map_insert__non_inited(void** state);
void test_map_insert__non_inited_pair(void** state);
void test_map_insert__pair_non_inited(void** state);
void test_map_insert__not_smae_type(void** state);
void test_map_insert__c_builtin_equal(void** state);
void test_map_insert__c_builtin_not_equal(void** state);
void test_map_insert__cstr_equal(void** state);
void test_map_insert__cstr_not_equal(void** state);
void test_map_insert__libcstl_builtin_equal(void** state);
void test_map_insert__libcstl_builtin_not_equal(void** state);
void test_map_insert__user_define_equal(void** state);
void test_map_insert__user_define_not_equal(void** state);
/*
 * test map_insert_hint
 */
UT_CASE_DECLARATION(map_insert_hint)
void test_map_insert_hint__null_map(void** state);
void test_map_insert_hint__null_pair(void** state);
void test_map_insert_hint__non_inited(void** state);
void test_map_insert_hint__non_inited_pair(void** state);
void test_map_insert_hint__pair_non_inited(void** state);
void test_map_insert_hint__hint_invalid_container_type(void** state);
void test_map_insert_hint__hint_invalid_iterator_type(void** state);
void test_map_insert_hint__hint_invalid_container(void** state);
void test_map_insert_hint__not_smae_type(void** state);
void test_map_insert_hint__c_builtin_equal(void** state);
void test_map_insert_hint__c_builtin_not_equal(void** state);
void test_map_insert_hint__cstr_equal(void** state);
void test_map_insert_hint__cstr_not_equal(void** state);
void test_map_insert_hint__libcstl_builtin_equal(void** state);
void test_map_insert_hint__libcstl_builtin_not_equal(void** state);
void test_map_insert_hint__user_define_equal(void** state);
void test_map_insert_hint__user_define_not_equal(void** state);
/*
 * test map_insert_range
 */
UT_CASE_DECLARATION(map_insert_range)
void test_map_insert_range__null_map(void** state);
void test_map_insert_range__non_inited(void** state);
void test_map_insert_range__non_inited_pair(void** state);
void test_map_insert_range__invalid_begin(void** state);
void test_map_insert_range__invalid_end(void** state);
void test_map_insert_range__invalid_range(void** state);
void test_map_insert_range__not_same_type(void** state);
void test_map_insert_range__empty(void** state);
void test_map_insert_range__non_empty_equal(void** state);
void test_map_insert_range__non_empty_dest_src_dup(void** state);
void test_map_insert_range__non_empty_src_dup(void** state);
void test_map_insert_range__compare(void** state);
void test_map_insert_range__other_container_range(void** state);
void test_map_insert_range__other_container_range_not_same_type(void** state);
/*void test_map_insert_range__other_container_range_not_pair(void** state);*/
/*
 * test map_insert_array
 */
UT_CASE_DECLARATION(map_insert_array)
void test_map_insert_array__null_map(void** state);
void test_map_insert_array__non_inited(void** state);
void test_map_insert_array__non_inited_pair(void** state);
void test_map_insert_array__invalid_array(void** state);
void test_map_insert_array__not_same_type(void** state);
void test_map_insert_array__empty(void** state);
void test_map_insert_array__non_empty_equal(void** state);
void test_map_insert_array__non_empty_dest_src_dup(void** state);
void test_map_insert_array__non_empty_src_dup(void** state);
/*void test_map_insert_array__array_not_pair(void** state);*/
/*
 * test map_erase_pos
 */
UT_CASE_DECLARATION(map_erase_pos)
void test_map_erase_pos__null_map(void** state);
void test_map_erase_pos__non_inited(void** state);
void test_map_erase_pos__non_inited_pair(void** state);
void test_map_erase_pos__invalid_pos(void** state);
void test_map_erase_pos__end(void** state);
void test_map_erase_pos__begin(void** state);
void test_map_erase_pos__middle(void** state);
void test_map_erase_pos__last(void** state);
void test_map_erase_pos__erase_empty(void** state);
/*
 * test map_erase_range
 */
UT_CASE_DECLARATION(map_erase_range)
void test_map_erase_range__null_map(void** state);
void test_map_erase_range__non_inited(void** state);
void test_map_erase_range__non_inited_pair(void** state);
void test_map_erase_range__invalid_begin(void** state);
void test_map_erase_range__invalid_end(void** state);
void test_map_erase_range__invalid_range(void** state);
void test_map_erase_range__empty(void** state);
void test_map_erase_range__begin(void** state);
void test_map_erase_range__middle(void** state);
void test_map_erase_range__end(void** state);
void test_map_erase_range__all(void** state);

#define UT_CSTL_MAP_CASE\
    UT_SUIT_BEGIN(cstl_map, test_map_init__null_map),\
    UT_CASE(test_map_init__non_created),\
    UT_CASE(test_map_init__non_created),\
    UT_CASE(test_map_init__null_compare),\
    UT_CASE_BEGIN(map_init_ex,  test_map_init_ex__null_map),\
    UT_CASE(test_map_init_ex__non_created),\
    UT_CASE(test_map_init_ex__non_created_pair),\
    UT_CASE(test_map_init_ex__null_compare),\
    UT_CASE(test_map_init_ex__non_null_compare),\
    UT_CASE_BEGIN(map_init_copy, test_map_init_copy__null_dest),\
    UT_CASE(test_map_init_copy__null_src),\
    UT_CASE(test_map_init_copy__non_created_dest),\
    UT_CASE(test_map_init_copy__non_created_dest_pair),\
    UT_CASE(test_map_init_copy__non_inited_src),\
    UT_CASE(test_map_init_copy__non_inited_src_pair),\
    UT_CASE(test_map_init_copy__not_same_type),\
    UT_CASE(test_map_init_copy__empty),\
    UT_CASE(test_map_init_copy__non_empty),\
    UT_CASE(test_map_init_copy__non_null_compare),\
    UT_CASE_BEGIN(map_init_copy_range, test_map_init_copy_range__null_map),\
    UT_CASE(test_map_init_copy_range__non_created_map),\
    UT_CASE(test_map_init_copy_range__non_created_map_pair),\
    UT_CASE(test_map_init_copy_range__invalid_begin),\
    UT_CASE(test_map_init_copy_range__invalid_end),\
    UT_CASE(test_map_init_copy_range__invalid_range),\
    UT_CASE(test_map_init_copy_range__invalid_range_not_same_type),\
    UT_CASE(test_map_init_copy_range__empty),\
    UT_CASE(test_map_init_copy_range__non_empty),\
    UT_CASE(test_map_init_copy_range__other_container_range),\
    UT_CASE(test_map_init_copy_range__other_container_range_dup),\
    UT_CASE(test_map_init_copy_range__other_container_range_not_same_type),\
    UT_CASE_BEGIN(map_init_copy_array, test_map_init_copy_array__null_map),\
    UT_CASE(test_map_init_copy_array__non_created_map),\
    UT_CASE(test_map_init_copy_array__non_created_map_pair),\
    UT_CASE(test_map_init_copy_array__invalid_array),\
    UT_CASE(test_map_init_copy_array__invalid_array_not_same_type),\
    UT_CASE(test_map_init_copy_array__empty),\
    UT_CASE(test_map_init_copy_array__non_empty),\
    UT_CASE(test_map_init_copy_array__non_empty_dup),\
    UT_CASE_BEGIN(map_init_copy_range_ex, test_map_init_copy_range_ex__null_map),\
    UT_CASE(test_map_init_copy_range_ex__non_created_map),\
    UT_CASE(test_map_init_copy_range_ex__non_created_map_pair),\
    UT_CASE(test_map_init_copy_range_ex__invalid_begin),\
    UT_CASE(test_map_init_copy_range_ex__invalid_end),\
    UT_CASE(test_map_init_copy_range_ex__invalid_range),\
    UT_CASE(test_map_init_copy_range_ex__invalid_range_not_same_type),\
    UT_CASE(test_map_init_copy_range_ex__empty),\
    UT_CASE(test_map_init_copy_range_ex__non_empty),\
    UT_CASE(test_map_init_copy_range_ex__compare),\
    UT_CASE(test_map_init_copy_range_ex__other_container_range),\
    UT_CASE(test_map_init_copy_range_ex__other_container_range_dup),\
    UT_CASE(test_map_init_copy_range_ex__other_container_range_not_same_type),\
    UT_CASE_BEGIN(map_init_copy_array_ex, test_map_init_copy_array_ex__null_map),\
    UT_CASE(test_map_init_copy_array_ex__non_created_map),\
    UT_CASE(test_map_init_copy_array_ex__non_created_map_pair),\
    UT_CASE(test_map_init_copy_array_ex__invalid_array),\
    UT_CASE(test_map_init_copy_array_ex__invalid_array_not_same_type),\
    UT_CASE(test_map_init_copy_array_ex__empty),\
    UT_CASE(test_map_init_copy_array_ex__non_empty),\
    UT_CASE(test_map_init_copy_array_ex__non_empty_dup),\
    UT_CASE(test_map_init_copy_array_ex__compare),\
    UT_CASE_BEGIN(map_destroy, test_map_destroy__null_map),\
    UT_CASE(test_map_destroy__non_created),\
    UT_CASE(test_map_destroy__created),\
    UT_CASE(test_map_destroy__inited),\
    UT_CASE(test_map_destroy__non_empty),\
    UT_CASE_BEGIN(map_assign, test_map_assign__null_dest),\
    UT_CASE(test_map_assign__null_src),\
    UT_CASE(test_map_assign__non_created_dest),\
    UT_CASE(test_map_assign__non_created_dest_pair),\
    UT_CASE(test_map_assign__non_init_src),\
    UT_CASE(test_map_assign__non_init_src_pair),\
    UT_CASE(test_map_assign__not_same_type),\
    UT_CASE(test_map_assign__empty_empty),\
    UT_CASE(test_map_assign__non_empty_empty),\
    UT_CASE(test_map_assign__non_empty_non_empty_less),\
    UT_CASE(test_map_assign__non_empty_non_empty_size_equal),\
    UT_CASE(test_map_assign__non_empty_non_empty_equal),\
    UT_CASE(test_map_assign__non_empty_non_empty_greater),\
    UT_CASE(test_map_assign__empty_non_empty),\
    UT_CASE_BEGIN(map_size, test_map_size__null_map),\
    UT_CASE(test_map_size__non_inited),\
    UT_CASE(test_map_size__non_inited_pair),\
    UT_CASE(test_map_size__empty),\
    UT_CASE(test_map_size__non_empty),\
    UT_CASE_BEGIN(map_empty, test_map_empty__null_map),\
    UT_CASE(test_map_empty__non_inited),\
    UT_CASE(test_map_empty__non_inited_pair),\
    UT_CASE(test_map_empty__empty),\
    UT_CASE(test_map_empty__non_empty),\
    UT_CASE_BEGIN(map_max_size, test_map_max_size__null_map),\
    UT_CASE(test_map_max_size__non_inited),\
    UT_CASE(test_map_max_size__non_inited_pair),\
    UT_CASE(test_map_max_size__empty),\
    UT_CASE(test_map_max_size__non_empty),\
    UT_CASE_BEGIN(map_begin, test_map_begin__null_map),\
    UT_CASE(test_map_begin__non_inited),\
    UT_CASE(test_map_begin__non_inited_pair),\
    UT_CASE(test_map_begin__empty),\
    UT_CASE(test_map_begin__non_empty),\
    UT_CASE_BEGIN(map_end, test_map_end__null_map),\
    UT_CASE(test_map_end__non_inited),\
    UT_CASE(test_map_end__non_inited_pair),\
    UT_CASE(test_map_end__empty),\
    UT_CASE(test_map_end__non_empty),\
    UT_CASE_BEGIN(map_key_comp, test_map_key_comp__null_map),\
    UT_CASE(test_map_key_comp__non_inited),\
    UT_CASE(test_map_key_comp__default_key_comp),\
    UT_CASE(test_map_key_comp__user_define_key_comp),\
    UT_CASE_BEGIN(map_value_comp, test_map_value_comp__null_map),\
    UT_CASE(test_map_value_comp__non_inited),\
    UT_CASE(test_map_value_comp__default_value_comp),\
    UT_CASE(test_map_value_comp__user_define_value_comp),\
    UT_CASE_BEGIN(map_clear, test_map_clear__null_map),\
    UT_CASE(test_map_clear__non_inited),\
    UT_CASE(test_map_clear__non_inited_pair),\
    UT_CASE(test_map_clear__empty),\
    UT_CASE(test_map_clear__non_empty),\
    UT_CASE_BEGIN(map_equal, test_map_equal__null_first),\
    UT_CASE(test_map_equal__null_second),\
    UT_CASE(test_map_equal__non_inited_first),\
    UT_CASE(test_map_equal__non_inited_first_pair),\
    UT_CASE(test_map_equal__non_inited_second),\
    UT_CASE(test_map_equal__non_inited_second_pair),\
    UT_CASE(test_map_equal__not_same_type),\
    UT_CASE(test_map_equal__same_map),\
    UT_CASE(test_map_equal__size_first_less_than_second),\
    UT_CASE(test_map_equal__size_first_greater_than_second),\
    UT_CASE(test_map_equal__size_equal_0),\
    UT_CASE(test_map_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_equal__compare_not_equal),\
    UT_CASE(test_map_equal__equal),\
    UT_CASE_BEGIN(map_not_equal, test_map_not_equal__null_first),\
    UT_CASE(test_map_not_equal__null_second),\
    UT_CASE(test_map_not_equal__non_inited_first),\
    UT_CASE(test_map_not_equal__non_inited_first_pair),\
    UT_CASE(test_map_not_equal__non_inited_second),\
    UT_CASE(test_map_not_equal__non_inited_second_pair),\
    UT_CASE(test_map_not_equal__not_same_type),\
    UT_CASE(test_map_not_equal__same_map),\
    UT_CASE(test_map_not_equal__size_first_less_than_second),\
    UT_CASE(test_map_not_equal__size_first_greater_than_second),\
    UT_CASE(test_map_not_equal__size_equal_0),\
    UT_CASE(test_map_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_not_equal__compare_not_equal),\
    UT_CASE(test_map_not_equal__equal),\
    UT_CASE_BEGIN(map_less, test_map_less__null_first),\
    UT_CASE(test_map_less__null_second),\
    UT_CASE(test_map_less__non_inited_first),\
    UT_CASE(test_map_less__non_inited_first_pair),\
    UT_CASE(test_map_less__non_inited_second),\
    UT_CASE(test_map_less__non_inited_second_pair),\
    UT_CASE(test_map_less__not_same_type),\
    UT_CASE(test_map_less__same_map),\
    UT_CASE(test_map_less__size_first_less_than_second),\
    UT_CASE(test_map_less__size_first_greater_than_second),\
    UT_CASE(test_map_less__size_equal_0),\
    UT_CASE(test_map_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_less__compare_less),\
    UT_CASE(test_map_less__equal),\
    UT_CASE_BEGIN(map_less_equal, test_map_less_equal__null_first),\
    UT_CASE(test_map_less_equal__null_second),\
    UT_CASE(test_map_less_equal__non_inited_first),\
    UT_CASE(test_map_less_equal__non_inited_first_pair),\
    UT_CASE(test_map_less_equal__non_inited_second),\
    UT_CASE(test_map_less_equal__non_inited_second_pair),\
    UT_CASE(test_map_less_equal__not_same_type),\
    UT_CASE(test_map_less_equal__same_map),\
    UT_CASE(test_map_less_equal__size_first_less_than_second),\
    UT_CASE(test_map_less_equal__size_first_greater_than_second),\
    UT_CASE(test_map_less_equal__size_equal_0),\
    UT_CASE(test_map_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_less_equal__compare_less),\
    UT_CASE(test_map_less_equal__equal),\
    UT_CASE_BEGIN(map_greater, test_map_greater__null_first),\
    UT_CASE(test_map_greater__null_second),\
    UT_CASE(test_map_greater__non_inited_first),\
    UT_CASE(test_map_greater__non_inited_first_pair),\
    UT_CASE(test_map_greater__non_inited_second),\
    UT_CASE(test_map_greater__non_inited_second_pair),\
    UT_CASE(test_map_greater__not_same_type),\
    UT_CASE(test_map_greater__same_map),\
    UT_CASE(test_map_greater__size_first_less_than_second),\
    UT_CASE(test_map_greater__size_first_greater_than_second),\
    UT_CASE(test_map_greater__size_equal_0),\
    UT_CASE(test_map_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_greater__compare_less),\
    UT_CASE(test_map_greater__equal),\
    UT_CASE_BEGIN(map_greater_equal, test_map_greater_equal__null_first),\
    UT_CASE(test_map_greater_equal__null_second),\
    UT_CASE(test_map_greater_equal__non_inited_first),\
    UT_CASE(test_map_greater_equal__non_inited_first_pair),\
    UT_CASE(test_map_greater_equal__non_inited_second),\
    UT_CASE(test_map_greater_equal__non_inited_second_pair),\
    UT_CASE(test_map_greater_equal__not_same_type),\
    UT_CASE(test_map_greater_equal__same_map),\
    UT_CASE(test_map_greater_equal__size_first_less_than_second),\
    UT_CASE(test_map_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_map_greater_equal__size_equal_0),\
    UT_CASE(test_map_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_map_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_map_greater_equal__compare_less),\
    UT_CASE(test_map_greater_equal__equal),\
    UT_CASE_BEGIN(map_swap, test_map_swap__null_first),\
    UT_CASE(test_map_swap__null_second),\
    UT_CASE(test_map_swap__non_inited_first),\
    UT_CASE(test_map_swap__non_inited_first_pair),\
    UT_CASE(test_map_swap__non_inited_second),\
    UT_CASE(test_map_swap__non_inited_second_pair),\
    UT_CASE(test_map_swap__not_same_type),\
    UT_CASE(test_map_swap__same_map),\
    UT_CASE(test_map_swap__0_swap_n),\
    UT_CASE(test_map_swap__n_swap_0),\
    UT_CASE(test_map_swap__n_swap_n),\
    UT_CASE(test_map_swap__m_swap_n),\
    UT_CASE_BEGIN(map_insert, test_map_insert__null_map),\
    UT_CASE(test_map_insert__null_pair),\
    UT_CASE(test_map_insert__non_inited),\
    UT_CASE(test_map_insert__non_inited_pair),\
    UT_CASE(test_map_insert__pair_non_inited),\
    UT_CASE(test_map_insert__not_smae_type),\
    UT_CASE(test_map_insert__c_builtin_equal),\
    UT_CASE(test_map_insert__c_builtin_not_equal),\
    UT_CASE(test_map_insert__cstr_equal),\
    UT_CASE(test_map_insert__cstr_not_equal),\
    UT_CASE(test_map_insert__libcstl_builtin_equal),\
    UT_CASE(test_map_insert__libcstl_builtin_not_equal),\
    UT_CASE(test_map_insert__user_define_equal),\
    UT_CASE(test_map_insert__user_define_not_equal),\
    UT_CASE_BEGIN(map_insert_hint, test_map_insert_hint__null_map),\
    UT_CASE(test_map_insert_hint__null_pair),\
    UT_CASE(test_map_insert_hint__non_inited),\
    UT_CASE(test_map_insert_hint__non_inited_pair),\
    UT_CASE(test_map_insert_hint__pair_non_inited),\
    UT_CASE(test_map_insert_hint__hint_invalid_container_type),\
    UT_CASE(test_map_insert_hint__hint_invalid_iterator_type),\
    UT_CASE(test_map_insert_hint__hint_invalid_container),\
    UT_CASE(test_map_insert_hint__not_smae_type),\
    UT_CASE(test_map_insert_hint__c_builtin_equal),\
    UT_CASE(test_map_insert_hint__c_builtin_not_equal),\
    UT_CASE(test_map_insert_hint__cstr_equal),\
    UT_CASE(test_map_insert_hint__cstr_not_equal),\
    UT_CASE(test_map_insert_hint__libcstl_builtin_equal),\
    UT_CASE(test_map_insert_hint__libcstl_builtin_not_equal),\
    UT_CASE(test_map_insert_hint__user_define_equal),\
    UT_CASE(test_map_insert_hint__user_define_not_equal),\
    UT_CASE_BEGIN(map_insert_range, test_map_insert_range__null_map),\
    UT_CASE(test_map_insert_range__non_inited),\
    UT_CASE(test_map_insert_range__non_inited_pair),\
    UT_CASE(test_map_insert_range__invalid_begin),\
    UT_CASE(test_map_insert_range__invalid_end),\
    UT_CASE(test_map_insert_range__invalid_range),\
    UT_CASE(test_map_insert_range__not_same_type),\
    UT_CASE(test_map_insert_range__empty),\
    UT_CASE(test_map_insert_range__non_empty_equal),\
    UT_CASE(test_map_insert_range__non_empty_dest_src_dup),\
    UT_CASE(test_map_insert_range__non_empty_src_dup),\
    UT_CASE(test_map_insert_range__compare),\
    UT_CASE(test_map_insert_range__other_container_range),\
    UT_CASE(test_map_insert_range__other_container_range_not_same_type),\
    UT_CASE_BEGIN(map_insert_array, test_map_insert_array__null_map),\
    UT_CASE(test_map_insert_array__non_inited),\
    UT_CASE(test_map_insert_array__non_inited_pair),\
    UT_CASE(test_map_insert_array__invalid_array),\
    UT_CASE(test_map_insert_array__not_same_type),\
    UT_CASE(test_map_insert_array__empty),\
    UT_CASE(test_map_insert_array__non_empty_equal),\
    UT_CASE(test_map_insert_array__non_empty_dest_src_dup),\
    UT_CASE(test_map_insert_array__non_empty_src_dup),\
    UT_CASE_BEGIN(map_erase_pos, test_map_erase_pos__null_map),\
    UT_CASE(test_map_erase_pos__non_inited),\
    UT_CASE(test_map_erase_pos__non_inited_pair),\
    UT_CASE(test_map_erase_pos__invalid_pos),\
    UT_CASE(test_map_erase_pos__end),\
    UT_CASE(test_map_erase_pos__begin),\
    UT_CASE(test_map_erase_pos__middle),\
    UT_CASE(test_map_erase_pos__last),\
    UT_CASE(test_map_erase_pos__erase_empty),\
    UT_CASE_BEGIN(map_erase_range, test_map_erase_range__null_map),\
    UT_CASE(test_map_erase_range__non_inited),\
    UT_CASE(test_map_erase_range__non_inited_pair),\
    UT_CASE(test_map_erase_range__invalid_begin),\
    UT_CASE(test_map_erase_range__invalid_end),\
    UT_CASE(test_map_erase_range__invalid_range),\
    UT_CASE(test_map_erase_range__empty),\
    UT_CASE(test_map_erase_range__begin),\
    UT_CASE(test_map_erase_range__middle),\
    UT_CASE(test_map_erase_range__end),\
    UT_CASE(test_map_erase_range__all)

#endif /* _UT_CSTL_MAP_H_ */

