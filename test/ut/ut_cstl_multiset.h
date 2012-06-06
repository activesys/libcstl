#ifndef _UT_CSTL_MULTISET_H_
#define _UT_CSTL_MULTISET_H_

UT_SUIT_DECLARATION(cstl_multiset)
/*
 * test multiset_init
 */
UT_CASE_DECLARATION(multiset_init)
void test_multiset_init__null_multiset(void** state);
void test_multiset_init__non_created(void** state);
void test_multiset_init__null_compare(void** state);
/*
 * test multiset_init_ex
 */
UT_CASE_DECLARATION(multiset_init_ex)
void test_multiset_init_ex__null_multiset(void** state);
void test_multiset_init_ex__non_created(void** state);
void test_multiset_init_ex__null_compare(void** state);
void test_multiset_init_ex__non_null_compare(void** state);
/*
 * test multiset_init_copy
 */
UT_CASE_DECLARATION(multiset_init_copy)
void test_multiset_init_copy__null_dest(void** state);
void test_multiset_init_copy__null_src(void** state);
void test_multiset_init_copy__non_created_dest(void** state);
void test_multiset_init_copy__non_inited_src(void** state);
void test_multiset_init_copy__not_same_type(void** state);
void test_multiset_init_copy__empty(void** state);
void test_multiset_init_copy__non_empty(void** state);
void test_multiset_init_copy__non_null_compare(void** state);
/*
 * test multiset_init_copy_range
 */
UT_CASE_DECLARATION(multiset_init_copy_range)
void test_multiset_init_copy_range__null_multiset(void** state);
void test_multiset_init_copy_range__non_created_multiset(void** state);
void test_multiset_init_copy_range__invalid_begin(void** state);
void test_multiset_init_copy_range__invalid_end(void** state);
void test_multiset_init_copy_range__invalid_range(void** state);
void test_multiset_init_copy_range__invalid_range_not_same_type(void** state);
void test_multiset_init_copy_range__empty(void** state);
void test_multiset_init_copy_range__non_empty(void** state);
void test_multiset_init_copy_range__other_container_range(void** state);
void test_multiset_init_copy_range__other_container_range_dup(void** state);
/*
 * test multiset_init_copy_array
 */
UT_CASE_DECLARATION(multiset_init_copy_array)
void test_multiset_init_copy_array__null_multiset(void** state);
void test_multiset_init_copy_array__non_created_multiset(void** state);
void test_multiset_init_copy_array__invalid_array(void** state);
void test_multiset_init_copy_array__empty(void** state);
void test_multiset_init_copy_array__non_empty(void** state);
void test_multiset_init_copy_array__non_empty_dup(void** state);
/*
 * test multiset_init_copy_range_ex
 */
UT_CASE_DECLARATION(multiset_init_copy_range_ex)
void test_multiset_init_copy_range_ex__null_multiset(void** state);
void test_multiset_init_copy_range_ex__non_created_multiset(void** state);
void test_multiset_init_copy_range_ex__invalid_begin(void** state);
void test_multiset_init_copy_range_ex__invalid_end(void** state);
void test_multiset_init_copy_range_ex__invalid_range(void** state);
void test_multiset_init_copy_range_ex__invalid_range_not_same_type(void** state);
void test_multiset_init_copy_range_ex__empty(void** state);
void test_multiset_init_copy_range_ex__non_empty(void** state);
void test_multiset_init_copy_range_ex__compare(void** state);
void test_multiset_init_copy_range_ex__other_container_range(void** state);
void test_multiset_init_copy_range_ex__other_container_range_dup(void** state);
/*
 * test multiset_init_copy_array_ex
 */
UT_CASE_DECLARATION(multiset_init_copy_array_ex)
void test_multiset_init_copy_array_ex__null_multiset(void** state);
void test_multiset_init_copy_array_ex__non_created_multiset(void** state);
void test_multiset_init_copy_array_ex__invalid_array(void** state);
void test_multiset_init_copy_array_ex__empty(void** state);
void test_multiset_init_copy_array_ex__non_empty(void** state);
void test_multiset_init_copy_array_ex__non_empty_dup(void** state);
void test_multiset_init_copy_array_ex__compare(void** state);
/*
 * test multiset_destroy
 */
UT_CASE_DECLARATION(multiset_destroy)
void test_multiset_destroy__null_multiset(void** state);
void test_multiset_destroy__non_created(void** state);
void test_multiset_destroy__created(void** state);
void test_multiset_destroy__inited(void** state);
/*
 * test multiset_assign
 */
UT_CASE_DECLARATION(multiset_assign)
void test_multiset_assign__null_dest(void** state);
void test_multiset_assign__null_src(void** state);
void test_multiset_assign__non_created_dest(void** state);
void test_multiset_assign__non_init_src(void** state);
void test_multiset_assign__not_same_type(void** state);
void test_multiset_assign__empty_empty(void** state);
void test_multiset_assign__non_empty_empty(void** state);
void test_multiset_assign__non_empty_non_empty_less(void** state);
void test_multiset_assign__non_empty_non_empty_size_equal(void** state);
void test_multiset_assign__non_empty_non_empty_equal(void** state);
void test_multiset_assign__non_empty_non_empty_greater(void** state);
void test_multiset_assign__empty_non_empty(void** state);
/*
 * test multiset_size
 */
UT_CASE_DECLARATION(multiset_size)
void test_multiset_size__null_multiset(void** state);
void test_multiset_size__non_inited(void** state);
void test_multiset_size__empty(void** state);
void test_multiset_size__non_empty(void** state);
/*
 * test _multiset_emtpy
 */
UT_CASE_DECLARATION(multiset_empty)
void test_multiset_empty__null_multiset(void** state);
void test_multiset_empty__non_inited(void** state);
void test_multiset_empty__empty(void** state);
void test_multiset_empty__non_empty(void** state);
/*
 * test multiset_max_size
 */
UT_CASE_DECLARATION(multiset_max_size)
void test_multiset_max_size__null_multiset(void** state);
void test_multiset_max_size__non_inited(void** state);
void test_multiset_max_size__empty(void** state);
void test_multiset_max_size__non_empty(void** state);
/*
 * test multiset_begin
 */
UT_CASE_DECLARATION(multiset_begin)
void test_multiset_begin__null_multiset(void** state);
void test_multiset_begin__non_inited(void** state);
void test_multiset_begin__empty(void** state);
void test_multiset_begin__non_empty(void** state);
/*
 * test multiset_end
 */
UT_CASE_DECLARATION(multiset_end)
void test_multiset_end__null_multiset(void** state);
void test_multiset_end__non_inited(void** state);
void test_multiset_end__empty(void** state);
void test_multiset_end__non_empty(void** state);
/*
 * test multiset_key_comp
 */
UT_CASE_DECLARATION(multiset_key_comp)
void test_multiset_key_comp__null_multiset(void** state);
void test_multiset_key_comp__non_inited(void** state);
void test_multiset_key_comp__default_key_comp(void** state);
void test_multiset_key_comp__user_define_key_comp(void** state);
/*
 * test multiset_clear
 */
UT_CASE_DECLARATION(multiset_clear)
void test_multiset_clear__null_multiset(void** state);
void test_multiset_clear__non_inited(void** state);
void test_multiset_clear__empty(void** state);
void test_multiset_clear__non_empty(void** state);
/*
 * test multiset_equal
 */
UT_CASE_DECLARATION(multiset_equal)
void test_multiset_equal__null_first(void** state);
void test_multiset_equal__null_second(void** state);
void test_multiset_equal__non_inited_first(void** state);
void test_multiset_equal__non_inited_second(void** state);
void test_multiset_equal__not_same_type(void** state);
void test_multiset_equal__same_multiset(void** state);
void test_multiset_equal__size_first_less_than_second(void** state);
void test_multiset_equal__size_first_greater_than_second(void** state);
void test_multiset_equal__size_equal_0(void** state);
void test_multiset_equal__size_equal_elem_first_less_than_second(void** state);
void test_multiset_equal__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_equal__compare_not_equal(void** state);
void test_multiset_equal__equal(void** state);
/*
 * test multiset_not_equal
 */
UT_CASE_DECLARATION(multiset_not_equal)
void test_multiset_not_equal__null_first(void** state);
void test_multiset_not_equal__null_second(void** state);
void test_multiset_not_equal__non_inited_first(void** state);
void test_multiset_not_equal__non_inited_second(void** state);
void test_multiset_not_equal__not_same_type(void** state);
void test_multiset_not_equal__same_multiset(void** state);
void test_multiset_not_equal__size_first_less_than_second(void** state);
void test_multiset_not_equal__size_first_greater_than_second(void** state);
void test_multiset_not_equal__size_equal_0(void** state);
void test_multiset_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_multiset_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_not_equal__compare_not_equal(void** state);
void test_multiset_not_equal__equal(void** state);
/*
 * test multiset_less
 */
UT_CASE_DECLARATION(multiset_less)
void test_multiset_less__null_first(void** state);
void test_multiset_less__null_second(void** state);
void test_multiset_less__non_inited_first(void** state);
void test_multiset_less__non_inited_second(void** state);
void test_multiset_less__not_same_type(void** state);
void test_multiset_less__same_multiset(void** state);
void test_multiset_less__size_first_less_than_second(void** state);
void test_multiset_less__size_first_greater_than_second(void** state);
void test_multiset_less__size_equal_0(void** state);
void test_multiset_less__size_equal_elem_first_less_than_second(void** state);
void test_multiset_less__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_less__compare_less(void** state);
void test_multiset_less__equal(void** state);
/*
 * test multiset_less_equal
 */
UT_CASE_DECLARATION(multiset_less_equal)
void test_multiset_less_equal__null_first(void** state);
void test_multiset_less_equal__null_second(void** state);
void test_multiset_less_equal__non_inited_first(void** state);
void test_multiset_less_equal__non_inited_second(void** state);
void test_multiset_less_equal__not_same_type(void** state);
void test_multiset_less_equal__same_multiset(void** state);
void test_multiset_less_equal__size_first_less_than_second(void** state);
void test_multiset_less_equal__size_first_greater_than_second(void** state);
void test_multiset_less_equal__size_equal_0(void** state);
void test_multiset_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_multiset_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_less_equal__compare_less(void** state);
void test_multiset_less_equal__equal(void** state);
/*
 * test multiset_greater
 */
UT_CASE_DECLARATION(multiset_greater)
void test_multiset_greater__null_first(void** state);
void test_multiset_greater__null_second(void** state);
void test_multiset_greater__non_inited_first(void** state);
void test_multiset_greater__non_inited_second(void** state);
void test_multiset_greater__not_same_type(void** state);
void test_multiset_greater__same_multiset(void** state);
void test_multiset_greater__size_first_less_than_second(void** state);
void test_multiset_greater__size_first_greater_than_second(void** state);
void test_multiset_greater__size_equal_0(void** state);
void test_multiset_greater__size_equal_elem_first_less_than_second(void** state);
void test_multiset_greater__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_greater__compare_less(void** state);
void test_multiset_greater__equal(void** state);
/*
 * test multiset_greater_equal
 */
UT_CASE_DECLARATION(multiset_greater_equal)
void test_multiset_greater_equal__null_first(void** state);
void test_multiset_greater_equal__null_second(void** state);
void test_multiset_greater_equal__non_inited_first(void** state);
void test_multiset_greater_equal__non_inited_second(void** state);
void test_multiset_greater_equal__not_same_type(void** state);
void test_multiset_greater_equal__same_multiset(void** state);
void test_multiset_greater_equal__size_first_less_than_second(void** state);
void test_multiset_greater_equal__size_first_greater_than_second(void** state);
void test_multiset_greater_equal__size_equal_0(void** state);
void test_multiset_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_multiset_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_multiset_greater_equal__compare_less(void** state);
void test_multiset_greater_equal__equal(void** state);
/*
 * test multiset_swap
 */
UT_CASE_DECLARATION(multiset_swap)
void test_multiset_swap__null_first(void** state);
void test_multiset_swap__null_second(void** state);
void test_multiset_swap__non_inited_first(void** state);
void test_multiset_swap__non_inited_second(void** state);
void test_multiset_swap__not_same_type(void** state);
void test_multiset_swap__same_multiset(void** state);
void test_multiset_swap__0_swap_n(void** state);
void test_multiset_swap__n_swap_0(void** state);
void test_multiset_swap__n_swap_n(void** state);
void test_multiset_swap__m_swap_n(void** state);
/*
 * test multiset_insert_range
 */
UT_CASE_DECLARATION(multiset_insert_range)
void test_multiset_insert_range__null_multiset(void** state);
void test_multiset_insert_range__non_inited(void** state);
void test_multiset_insert_range__invalid_begin(void** state);
void test_multiset_insert_range__invalid_end(void** state);
void test_multiset_insert_range__invalid_range(void** state);
void test_multiset_insert_range__not_same_type(void** state);
void test_multiset_insert_range__empty(void** state);
void test_multiset_insert_range__non_empty_equal(void** state);
void test_multiset_insert_range__non_empty_dest_src_dup(void** state);
void test_multiset_insert_range__non_empty_src_dup(void** state);
void test_multiset_insert_range__compare(void** state);
void test_multiset_insert_range__other_container_range(void** state);
/*
 * test multiset_insert_array
 */
UT_CASE_DECLARATION(multiset_insert_array)
void test_multiset_insert_array__null_multiset(void** state);
void test_multiset_insert_array__non_inited(void** state);
void test_multiset_insert_array__invalid_array(void** state);
void test_multiset_insert_array__empty(void** state);
void test_multiset_insert_array__non_empty_equal(void** state);
void test_multiset_insert_array__non_empty_dest_src_dup(void** state);
void test_multiset_insert_array__non_empty_src_dup(void** state);
/*
 * test multiset_erase_pos
 */
UT_CASE_DECLARATION(multiset_erase_pos)
void test_multiset_erase_pos__null_multiset(void** state);
void test_multiset_erase_pos__non_inited(void** state);
void test_multiset_erase_pos__invalid_pos(void** state);
void test_multiset_erase_pos__end(void** state);
void test_multiset_erase_pos__begin(void** state);
void test_multiset_erase_pos__middle(void** state);
void test_multiset_erase_pos__last(void** state);
void test_multiset_erase_pos__erase_empty(void** state);
/*
 * test multiset_erase_range
 */
UT_CASE_DECLARATION(multiset_erase_range)
void test_multiset_erase_range__null_multiset(void** state);
void test_multiset_erase_range__non_inited(void** state);
void test_multiset_erase_range__invalid_begin(void** state);
void test_multiset_erase_range__invalid_end(void** state);
void test_multiset_erase_range__invalid_range(void** state);
void test_multiset_erase_range__empty(void** state);
void test_multiset_erase_range__begin(void** state);
void test_multiset_erase_range__middle(void** state);
void test_multiset_erase_range__end(void** state);
void test_multiset_erase_range__all(void** state);

#define UT_CSTL_MULTISET_CASE\
    UT_SUIT_BEGIN(cstl_multiset, test_multiset_init__null_multiset),\
    UT_CASE(test_multiset_init__non_created),\
    UT_CASE(test_multiset_init__null_compare),\
    UT_CASE_BEGIN(multiset_init_ex,  test_multiset_init_ex__null_multiset),\
    UT_CASE(test_multiset_init_ex__non_created),\
    UT_CASE(test_multiset_init_ex__null_compare),\
    UT_CASE(test_multiset_init_ex__non_null_compare),\
    UT_CASE_BEGIN(multiset_init_copy, test_multiset_init_copy__null_dest),\
    UT_CASE(test_multiset_init_copy__null_src),\
    UT_CASE(test_multiset_init_copy__non_created_dest),\
    UT_CASE(test_multiset_init_copy__non_inited_src),\
    UT_CASE(test_multiset_init_copy__not_same_type),\
    UT_CASE(test_multiset_init_copy__empty),\
    UT_CASE(test_multiset_init_copy__non_empty),\
    UT_CASE(test_multiset_init_copy__non_null_compare),\
    UT_CASE_BEGIN(multiset_init_copy_range, test_multiset_init_copy_range__null_multiset),\
    UT_CASE(test_multiset_init_copy_range__non_created_multiset),\
    UT_CASE(test_multiset_init_copy_range__invalid_begin),\
    UT_CASE(test_multiset_init_copy_range__invalid_end),\
    UT_CASE(test_multiset_init_copy_range__invalid_range),\
    UT_CASE(test_multiset_init_copy_range__invalid_range_not_same_type),\
    UT_CASE(test_multiset_init_copy_range__empty),\
    UT_CASE(test_multiset_init_copy_range__non_empty),\
    UT_CASE(test_multiset_init_copy_range__other_container_range),\
    UT_CASE(test_multiset_init_copy_range__other_container_range_dup),\
    UT_CASE_BEGIN(multiset_init_copy_array, test_multiset_init_copy_array__null_multiset),\
    UT_CASE(test_multiset_init_copy_array__non_created_multiset),\
    UT_CASE(test_multiset_init_copy_array__invalid_array),\
    UT_CASE(test_multiset_init_copy_array__empty),\
    UT_CASE(test_multiset_init_copy_array__non_empty),\
    UT_CASE(test_multiset_init_copy_array__non_empty_dup),\
    UT_CASE_BEGIN(multiset_init_copy_range_ex, test_multiset_init_copy_range_ex__null_multiset),\
    UT_CASE(test_multiset_init_copy_range_ex__non_created_multiset),\
    UT_CASE(test_multiset_init_copy_range_ex__invalid_begin),\
    UT_CASE(test_multiset_init_copy_range_ex__invalid_end),\
    UT_CASE(test_multiset_init_copy_range_ex__invalid_range),\
    UT_CASE(test_multiset_init_copy_range_ex__invalid_range_not_same_type),\
    UT_CASE(test_multiset_init_copy_range_ex__empty),\
    UT_CASE(test_multiset_init_copy_range_ex__non_empty),\
    UT_CASE(test_multiset_init_copy_range_ex__compare),\
    UT_CASE(test_multiset_init_copy_range_ex__other_container_range),\
    UT_CASE(test_multiset_init_copy_range_ex__other_container_range_dup),\
    UT_CASE_BEGIN(multiset_init_copy_array_ex, test_multiset_init_copy_array_ex__null_multiset),\
    UT_CASE(test_multiset_init_copy_array_ex__non_created_multiset),\
    UT_CASE(test_multiset_init_copy_array_ex__invalid_array),\
    UT_CASE(test_multiset_init_copy_array_ex__empty),\
    UT_CASE(test_multiset_init_copy_array_ex__non_empty),\
    UT_CASE(test_multiset_init_copy_array_ex__non_empty_dup),\
    UT_CASE(test_multiset_init_copy_array_ex__compare),\
    UT_CASE_BEGIN(multiset_destroy, test_multiset_destroy__null_multiset),\
    UT_CASE(test_multiset_destroy__non_created),\
    UT_CASE(test_multiset_destroy__created),\
    UT_CASE(test_multiset_destroy__inited),\
    UT_CASE_BEGIN(multiset_assign, test_multiset_assign__null_dest),\
    UT_CASE(test_multiset_assign__null_src),\
    UT_CASE(test_multiset_assign__non_created_dest),\
    UT_CASE(test_multiset_assign__non_init_src),\
    UT_CASE(test_multiset_assign__not_same_type),\
    UT_CASE(test_multiset_assign__empty_empty),\
    UT_CASE(test_multiset_assign__non_empty_empty),\
    UT_CASE(test_multiset_assign__non_empty_non_empty_less),\
    UT_CASE(test_multiset_assign__non_empty_non_empty_size_equal),\
    UT_CASE(test_multiset_assign__non_empty_non_empty_equal),\
    UT_CASE(test_multiset_assign__non_empty_non_empty_greater),\
    UT_CASE(test_multiset_assign__empty_non_empty),\
    UT_CASE_BEGIN(multiset_size, test_multiset_size__null_multiset),\
    UT_CASE(test_multiset_size__non_inited),\
    UT_CASE(test_multiset_size__empty),\
    UT_CASE(test_multiset_size__non_empty),\
    UT_CASE_BEGIN(multiset_empty, test_multiset_empty__null_multiset),\
    UT_CASE(test_multiset_empty__non_inited),\
    UT_CASE(test_multiset_empty__empty),\
    UT_CASE(test_multiset_empty__non_empty),\
    UT_CASE_BEGIN(multiset_max_size, test_multiset_max_size__null_multiset),\
    UT_CASE(test_multiset_max_size__non_inited),\
    UT_CASE(test_multiset_max_size__empty),\
    UT_CASE(test_multiset_max_size__non_empty),\
    UT_CASE_BEGIN(multiset_begin, test_multiset_begin__null_multiset),\
    UT_CASE(test_multiset_begin__non_inited),\
    UT_CASE(test_multiset_begin__empty),\
    UT_CASE(test_multiset_begin__non_empty),\
    UT_CASE_BEGIN(multiset_end, test_multiset_end__null_multiset),\
    UT_CASE(test_multiset_end__non_inited),\
    UT_CASE(test_multiset_end__empty),\
    UT_CASE(test_multiset_end__non_empty),\
    UT_CASE_BEGIN(multiset_key_comp, test_multiset_key_comp__null_multiset),\
    UT_CASE(test_multiset_key_comp__non_inited),\
    UT_CASE(test_multiset_key_comp__default_key_comp),\
    UT_CASE(test_multiset_key_comp__user_define_key_comp),\
    UT_CASE_BEGIN(multiset_clear, test_multiset_clear__null_multiset),\
    UT_CASE(test_multiset_clear__non_inited),\
    UT_CASE(test_multiset_clear__empty),\
    UT_CASE(test_multiset_clear__non_empty),\
    UT_CASE_BEGIN(multiset_equal, test_multiset_equal__null_first),\
    UT_CASE(test_multiset_equal__null_second),\
    UT_CASE(test_multiset_equal__non_inited_first),\
    UT_CASE(test_multiset_equal__non_inited_second),\
    UT_CASE(test_multiset_equal__not_same_type),\
    UT_CASE(test_multiset_equal__same_multiset),\
    UT_CASE(test_multiset_equal__size_first_less_than_second),\
    UT_CASE(test_multiset_equal__size_first_greater_than_second),\
    UT_CASE(test_multiset_equal__size_equal_0),\
    UT_CASE(test_multiset_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_equal__compare_not_equal),\
    UT_CASE(test_multiset_equal__equal),\
    UT_CASE_BEGIN(multiset_not_equal, test_multiset_not_equal__null_first),\
    UT_CASE(test_multiset_not_equal__null_second),\
    UT_CASE(test_multiset_not_equal__non_inited_first),\
    UT_CASE(test_multiset_not_equal__non_inited_second),\
    UT_CASE(test_multiset_not_equal__not_same_type),\
    UT_CASE(test_multiset_not_equal__same_multiset),\
    UT_CASE(test_multiset_not_equal__size_first_less_than_second),\
    UT_CASE(test_multiset_not_equal__size_first_greater_than_second),\
    UT_CASE(test_multiset_not_equal__size_equal_0),\
    UT_CASE(test_multiset_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_not_equal__compare_not_equal),\
    UT_CASE(test_multiset_not_equal__equal),\
    UT_CASE_BEGIN(multiset_less, test_multiset_less__null_first),\
    UT_CASE(test_multiset_less__null_second),\
    UT_CASE(test_multiset_less__non_inited_first),\
    UT_CASE(test_multiset_less__non_inited_second),\
    UT_CASE(test_multiset_less__not_same_type),\
    UT_CASE(test_multiset_less__same_multiset),\
    UT_CASE(test_multiset_less__size_first_less_than_second),\
    UT_CASE(test_multiset_less__size_first_greater_than_second),\
    UT_CASE(test_multiset_less__size_equal_0),\
    UT_CASE(test_multiset_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_less__compare_less),\
    UT_CASE(test_multiset_less__equal),\
    UT_CASE_BEGIN(multiset_less_equal, test_multiset_less_equal__null_first),\
    UT_CASE(test_multiset_less_equal__null_second),\
    UT_CASE(test_multiset_less_equal__non_inited_first),\
    UT_CASE(test_multiset_less_equal__non_inited_second),\
    UT_CASE(test_multiset_less_equal__not_same_type),\
    UT_CASE(test_multiset_less_equal__same_multiset),\
    UT_CASE(test_multiset_less_equal__size_first_less_than_second),\
    UT_CASE(test_multiset_less_equal__size_first_greater_than_second),\
    UT_CASE(test_multiset_less_equal__size_equal_0),\
    UT_CASE(test_multiset_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_less_equal__compare_less),\
    UT_CASE(test_multiset_less_equal__equal),\
    UT_CASE_BEGIN(multiset_greater, test_multiset_greater__null_first),\
    UT_CASE(test_multiset_greater__null_second),\
    UT_CASE(test_multiset_greater__non_inited_first),\
    UT_CASE(test_multiset_greater__non_inited_second),\
    UT_CASE(test_multiset_greater__not_same_type),\
    UT_CASE(test_multiset_greater__same_multiset),\
    UT_CASE(test_multiset_greater__size_first_less_than_second),\
    UT_CASE(test_multiset_greater__size_first_greater_than_second),\
    UT_CASE(test_multiset_greater__size_equal_0),\
    UT_CASE(test_multiset_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_greater__compare_less),\
    UT_CASE(test_multiset_greater__equal),\
    UT_CASE_BEGIN(multiset_greater_equal, test_multiset_greater_equal__null_first),\
    UT_CASE(test_multiset_greater_equal__null_second),\
    UT_CASE(test_multiset_greater_equal__non_inited_first),\
    UT_CASE(test_multiset_greater_equal__non_inited_second),\
    UT_CASE(test_multiset_greater_equal__not_same_type),\
    UT_CASE(test_multiset_greater_equal__same_multiset),\
    UT_CASE(test_multiset_greater_equal__size_first_less_than_second),\
    UT_CASE(test_multiset_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_multiset_greater_equal__size_equal_0),\
    UT_CASE(test_multiset_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_multiset_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_multiset_greater_equal__compare_less),\
    UT_CASE(test_multiset_greater_equal__equal),\
    UT_CASE_BEGIN(multiset_swap, test_multiset_swap__null_first),\
    UT_CASE(test_multiset_swap__null_second),\
    UT_CASE(test_multiset_swap__non_inited_first),\
    UT_CASE(test_multiset_swap__non_inited_second),\
    UT_CASE(test_multiset_swap__not_same_type),\
    UT_CASE(test_multiset_swap__same_multiset),\
    UT_CASE(test_multiset_swap__0_swap_n),\
    UT_CASE(test_multiset_swap__n_swap_0),\
    UT_CASE(test_multiset_swap__n_swap_n),\
    UT_CASE(test_multiset_swap__m_swap_n),\
    UT_CASE_BEGIN(multiset_insert_range, test_multiset_insert_range__null_multiset),\
    UT_CASE(test_multiset_insert_range__non_inited),\
    UT_CASE(test_multiset_insert_range__invalid_begin),\
    UT_CASE(test_multiset_insert_range__invalid_end),\
    UT_CASE(test_multiset_insert_range__invalid_range),\
    UT_CASE(test_multiset_insert_range__not_same_type),\
    UT_CASE(test_multiset_insert_range__empty),\
    UT_CASE(test_multiset_insert_range__non_empty_equal),\
    UT_CASE(test_multiset_insert_range__non_empty_dest_src_dup),\
    UT_CASE(test_multiset_insert_range__non_empty_src_dup),\
    UT_CASE(test_multiset_insert_range__compare),\
    UT_CASE(test_multiset_insert_range__other_container_range),\
    UT_CASE_BEGIN(multiset_insert_array, test_multiset_insert_array__null_multiset),\
    UT_CASE(test_multiset_insert_array__non_inited),\
    UT_CASE(test_multiset_insert_array__invalid_array),\
    UT_CASE(test_multiset_insert_array__empty),\
    UT_CASE(test_multiset_insert_array__non_empty_equal),\
    UT_CASE(test_multiset_insert_array__non_empty_dest_src_dup),\
    UT_CASE(test_multiset_insert_array__non_empty_src_dup),\
    UT_CASE_BEGIN(multiset_erase_pos, test_multiset_erase_pos__null_multiset),\
    UT_CASE(test_multiset_erase_pos__non_inited),\
    UT_CASE(test_multiset_erase_pos__invalid_pos),\
    UT_CASE(test_multiset_erase_pos__end),\
    UT_CASE(test_multiset_erase_pos__begin),\
    UT_CASE(test_multiset_erase_pos__middle),\
    UT_CASE(test_multiset_erase_pos__last),\
    UT_CASE(test_multiset_erase_pos__erase_empty),\
    UT_CASE_BEGIN(multiset_erase_range, test_multiset_erase_range__null_multiset),\
    UT_CASE(test_multiset_erase_range__non_inited),\
    UT_CASE(test_multiset_erase_range__invalid_begin),\
    UT_CASE(test_multiset_erase_range__invalid_end),\
    UT_CASE(test_multiset_erase_range__invalid_range),\
    UT_CASE(test_multiset_erase_range__empty),\
    UT_CASE(test_multiset_erase_range__begin),\
    UT_CASE(test_multiset_erase_range__middle),\
    UT_CASE(test_multiset_erase_range__end),\
    UT_CASE(test_multiset_erase_range__all)

#endif /* _UT_CSTL_MULTISET_H_ */

