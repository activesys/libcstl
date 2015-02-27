#ifndef _UT_CSTL_DEQUE_H_
#define _UT_CSTL_DEQUE_H_

UT_SUIT_DECLARATION(cstl_deque)

/*
 * test deque_init
 */
UT_CASE_DECLARATION(deque_init)
void test_deque_init__null_deque_container(void** state);
void test_deque_init__non_created_deque_container(void** state);
void test_deque_init__successfully(void** state);
/*
 * test deque_init_n
 */
UT_CASE_DECLARATION(deque_init_n)
void test_deque_init_n__null_deque_container(void** state);
void test_deque_init_n__non_created_deque_container(void** state);
void test_deque_init_n__empty(void** state);
void test_deque_init_n__c_builtin(void** state);
void test_deque_init_n__cstr(void** stat);
void test_deque_init_n__libcstl_builtin(void** state);
void test_deque_init_n__user_define(void** state);
void test_deque_init_n__one_chunk(void** state);
void test_deque_init_n__more_than_one_chunk(void** state);
void test_deque_init_n__map_grow(void** state);
/*
 * test deque_init_copy
 */
UT_CASE_DECLARATION(deque_init_copy)
void test_deque_init_copy__null_dest_deque_container(void** state);
void test_deque_init_copy__null_src_deque_container(void** state);
void test_deque_init_copy__non_created_dest_deque_container(void** state);
void test_deque_init_copy__non_inited_src_deque_container(void** state);
void test_deque_init_copy__not_same_type(void** state);
void test_deque_init_copy__init_copy_empty(void** state);
void test_deque_init_copy__c_builtin(void** state);
void test_deque_init_copy__cstr(void** state);
void test_deque_init_copy__libcstl_builtin(void** state);
void test_deque_init_copy__user_define(void** state);
/*
 * test deque_init_copy_range
 */
UT_CASE_DECLARATION(deque_init_copy_range)
void test_deque_init_copy_range__null_deque_container(void** state);
void test_deque_init_copy_range__non_created_deque_container(void** state);
void test_deque_init_copy_range__invalid_range(void** state);
void test_deque_init_copy_range__not_same(void** state);
void test_deque_init_copy_range__init_copy_range_empty(void** state);
void test_deque_init_copy_range__c_builtin(void** state);
void test_deque_init_copy_range__cstr(void** state);
void test_deque_init_copy_range__libcstl_builtin(void** state);
void test_deque_init_copy_range__user_define(void** state);
void test_deque_init_copy_range__other_container_range(void** state);
void test_deque_init_copy_range__other_container_range_1(void** state);
/*
 * test deque_init_copy_array
 */
UT_CASE_DECLARATION(deque_init_copy_array)
void test_deque_init_copy_array__null_deque_container(void** state);
void test_deque_init_copy_array__non_created_deque_container(void** state);
void test_deque_init_copy_array__null_array(void** state);
void test_deque_init_copy_array__init_copy_array_empty(void** state);
void test_deque_init_copy_array__c_builtin(void** state);
void test_deque_init_copy_array__cstr(void** state);
void test_deque_init_copy_array__libcstl_builtin(void** state);
void test_deque_init_copy_array__user_define(void** state);
void test_deque_init_copy_array__other_container_array_1(void** state);
/*
 * test deque_destroy
 */
UT_CASE_DECLARATION(deque_destroy)
void test_deque_destroy__null_deque_container(void** state);
void test_deque_destroy__non_created_deque_container(void** state);
void test_deque_destroy__created_non_inited(void** state);
void test_deque_destroy__empty(void** state);
void test_deque_destroy__non_empty(void** state);
/*
 * test deque_size
 */
UT_CASE_DECLARATION(deque_size)
void test_deque_size__null_deque_container(void** state);
void test_deque_size__non_inited_deque_container(void** state);
void test_deque_size__empty(void** state);
void test_deque_size__non_empty(void** state);
/*
 * test deque_empty
 */
UT_CASE_DECLARATION(deque_empty)
void test_deque_empty__null_deque_container(void** state);
void test_deque_empty__non_inited_deque_container(void** state);
void test_deque_empty__empty(void** state);
void test_deque_empty__non_empty(void** state);
/*
 * test deque_max_size
 */
UT_CASE_DECLARATION(deque_max_size)
void test_deque_max_size__null_deque_container(void** state);
void test_deque_max_size__non_inited_deque_container(void** state);
void test_deque_max_size__empty(void** state);
void test_deque_max_size__non_empty(void** state);
/*
 * test deque_begin
 */
UT_CASE_DECLARATION(deque_begin)
void test_deque_begin__null_deque_container(void** state);
void test_deque_begin__non_inited_deque_container(void** state);
void test_deque_begin__empty(void** state);
void test_deque_begin__non_empty(void** state);
/*
 * test deque_end
 */
UT_CASE_DECLARATION(deque_end)
void test_deque_end__null_deque_container(void** state);
void test_deque_end__non_inited_deque_container(void** state);
void test_deque_end__empty(void** state);
void test_deque_end__non_empty(void** state);
/*
 * test deque_assign
 */
UT_CASE_DECLARATION(deque_assign)
void test_deque_assign__null_dest(void** state);
void test_deque_assign__null_src(void** state);
void test_deque_assign__non_inited_dest(void** state);
void test_deque_assign__non_inited_src(void** state);
void test_deque_assign__not_same_type(void** state);
void test_deque_assign__same_container(void** state);
void test_deque_assign__0_assign_0(void** state);
void test_deque_assign__0_assign_10(void** state);
void test_deque_assign__10_assign_0(void** state);
void test_deque_assign__10_assign_10_deque_equal(void** state);
void test_deque_assign__10_assign_10_deque_not_equal(void** state);
void test_deque_assign__10_assign_1000(void** state);
/*
 * test deque_assign_range
 */
UT_CASE_DECLARATION(deque_assign_range)
void test_deque_assign_range__null_deque_container(void** state);
void test_deque_assign_range__non_inited(void** state);
void test_deque_assign_range__invalid_it_begin(void** state);
void test_deque_assign_range__invalid_it_end(void** state);
void test_deque_assign_range__invalid_range(void** state);
void test_deque_assign_range__invalid_range_not_same_type(void** state);
void test_deque_assign_range__range_belong_to_deque(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_begin(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_end(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_front(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_middle(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_back(void** state);
void test_deque_assign_range__range_belong_to_deque_not_empty_full(void** state);
void test_deque_assign_range__0_assign_range_0(void** state);
void test_deque_assign_range__0_assign_range_10(void** state);
void test_deque_assign_range__10_assign_range_0(void** state);
void test_deque_assign_range__10_assign_range_10_same_elem(void** state);
void test_deque_assign_range__10_assign_range_10_not_same_elem(void** state);
void test_deque_assign_range__10_assign_range_1000(void** state);
void test_deque_assign_range__other_container_range(void** state);
void test_deque_assign_range__other_container_range1(void** state);
/*
 * test deque_assign_array
 */
UT_CASE_DECLARATION(deque_assign_array)
void test_deque_assign_array__null_deque_container(void** state);
void test_deque_assign_array__non_inited(void** state);
void test_deque_assign_array__null_array(void** state);
void test_deque_assign_array__0_assign_array_0(void** state);
void test_deque_assign_array__0_assign_array_10(void** state);
void test_deque_assign_array__10_assign_array_0(void** state);
void test_deque_assign_array__10_assign_array_10_same_elem(void** state);
void test_deque_assign_array__10_assign_array_10_not_same_elem(void** state);
void test_deque_assign_array__10_assign_array_1000(void** state);
void test_deque_assign_array__other_container_array(void** state);
void test_deque_assign_array__user_define(void** state);
void test_deque_assign_array__cstr(void** state);
/*
 * test deque_equal
 */
UT_CASE_DECLARATION(deque_equal)
void test_deque_equal__null_first(void** state);
void test_deque_equal__null_second(void** state);
void test_deque_equal__non_inited_first(void** state);
void test_deque_equal__non_inited_second(void** state);
void test_deque_equal__not_same_type(void** state);
void test_deque_equal__same_deque(void** state);
void test_deque_equal__size_first_less_than_second(void** state);
void test_deque_equal__size_first_greater_than_second(void** state);
void test_deque_equal__size_equal_0(void** state);
void test_deque_equal__size_equal_elem_first_less_than_second(void** state);
void test_deque_equal__size_equal_elem_first_greater_than_second(void** state);
void test_deque_equal__size_equal_elem_equal(void** state);
/*
 * test deque_not_equal
 */
UT_CASE_DECLARATION(deque_not_equal)
void test_deque_not_equal__null_first(void** state);
void test_deque_not_equal__null_second(void** state);
void test_deque_not_equal__non_inited_first(void** state);
void test_deque_not_equal__non_inited_second(void** state);
void test_deque_not_equal__not_same_type(void** state);
void test_deque_not_equal__same_deque(void** state);
void test_deque_not_equal__size_first_less_than_second(void** state);
void test_deque_not_equal__size_first_greater_than_second(void** state);
void test_deque_not_equal__size_equal_0(void** state);
void test_deque_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_deque_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_deque_not_equal__size_equal_elem_equal(void** state);
/*
 * test deque_less
 */
UT_CASE_DECLARATION(deque_less)
void test_deque_less__null_first(void** state);
void test_deque_less__null_second(void** state);
void test_deque_less__non_inited_first(void** state);
void test_deque_less__non_inited_second(void** state);
void test_deque_less__not_same_type(void** state);
void test_deque_less__same_deque(void** state);
void test_deque_less__size_first_less_than_second(void** state);
void test_deque_less__size_first_greater_than_second(void** state);
void test_deque_less__size_equal_0(void** state);
void test_deque_less__size_equal_elem_first_less_than_second(void** state);
void test_deque_less__size_equal_elem_first_greater_than_second(void** state);
void test_deque_less__size_equal_elem_equal(void** state);
/*
 * test deque_less_equal
 */
UT_CASE_DECLARATION(deque_less_equal)
void test_deque_less_equal__null_first(void** state);
void test_deque_less_equal__null_second(void** state);
void test_deque_less_equal__non_inited_first(void** state);
void test_deque_less_equal__non_inited_second(void** state);
void test_deque_less_equal__not_same_type(void** state);
void test_deque_less_equal__same_deque(void** state);
void test_deque_less_equal__size_first_less_than_second(void** state);
void test_deque_less_equal__size_first_greater_than_second(void** state);
void test_deque_less_equal__size_equal_0(void** state);
void test_deque_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_deque_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_deque_less_equal__size_equal_elem_equal(void** state);
/*
 * test deque_greater
 */
UT_CASE_DECLARATION(deque_greater)
void test_deque_greater__null_first(void** state);
void test_deque_greater__null_second(void** state);
void test_deque_greater__non_inited_first(void** state);
void test_deque_greater__non_inited_second(void** state);
void test_deque_greater__not_same_type(void** state);
void test_deque_greater__same_deque(void** state);
void test_deque_greater__size_first_less_than_second(void** state);
void test_deque_greater__size_first_greater_than_second(void** state);
void test_deque_greater__size_equal_0(void** state);
void test_deque_greater__size_equal_elem_first_less_than_second(void** state);
void test_deque_greater__size_equal_elem_first_greater_than_second(void** state);
void test_deque_greater__size_equal_elem_equal(void** state);
/*
 * test deque_greater_equal
 */
UT_CASE_DECLARATION(deque_greater_equal)
void test_deque_greater_equal__null_first(void** state);
void test_deque_greater_equal__null_second(void** state);
void test_deque_greater_equal__non_inited_first(void** state);
void test_deque_greater_equal__non_inited_second(void** state);
void test_deque_greater_equal__not_same_type(void** state);
void test_deque_greater_equal__same_deque(void** state);
void test_deque_greater_equal__size_first_less_than_second(void** state);
void test_deque_greater_equal__size_first_greater_than_second(void** state);
void test_deque_greater_equal__size_equal_0(void** state);
void test_deque_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_deque_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_deque_greater_equal__size_equal_elem_equal(void** state);
/*
 * test deque_at
 */
UT_CASE_DECLARATION(deque_at)
void test_deque_at__null_deque_container(void** state);
void test_deque_at__non_inited_deque_container(void** state);
void test_deque_at__invalid_subscript_empty(void** state);
void test_deque_at__invalid_subscript_end(void** state);
void test_deque_at__invalid_subscript(void** state);
void test_deque_at__successfully(void** state);
void test_deque_at__successfully_cstr(void** state);
/*
 * test deque_front
 */
UT_CASE_DECLARATION(deque_front)
void test_deque_front__null_deque_container(void** state);
void test_deque_front__non_inited_deque_container(void** state);
void test_deque_front__empty(void** state);
void test_deque_front__successfully(void** state);
void test_deque_front__successfully_cstr(void** state);
/*
 * test deque_back
 */
UT_CASE_DECLARATION(deque_back)
void test_deque_back__null_deque_container(void** state);
void test_deque_back__non_inited_deque_container(void** state);
void test_deque_back__empty(void** state);
void test_deque_back__successfully(void** state);
void test_deque_back__successfully_cstr(void** state);
/*
 * test deque_swap
 */
UT_CASE_DECLARATION(deque_swap)
void test_deque_swap__null_first(void** state);
void test_deque_swap__null_second(void** state);
void test_deque_swap__non_inited_first(void** state);
void test_deque_swap__non_inited_second(void** state);
void test_deque_swap__not_same_type(void** state);
void test_deque_swap__deque_equal(void** state);
void test_deque_swap__0_swap_10(void** state);
void test_deque_swap__10_swap_0(void** state);
void test_deque_swap__10_swap_10(void** state);
void test_deque_swap__10_swap_1000(void** state);
/*
 * test deque_pop_back
 */
UT_CASE_DECLARATION(deque_pop_back)
void test_deque_pop_back__null_deque_container(void** state);
void test_deque_pop_back__non_inited_deque_container(void** state);
void test_deque_pop_back__empty(void** state);
void test_deque_pop_back__successfully(void** state);
/*
 * test deque_pop_front
 */
UT_CASE_DECLARATION(deque_pop_front)
void test_deque_pop_front__null_deque_container(void** state);
void test_deque_pop_front__non_inited_deque_container(void** state);
void test_deque_pop_front__empty(void** state);
void test_deque_pop_front__successfully(void** state);
/*
 * test deque_insert_range
 */
UT_CASE_DECLARATION(deque_insert_range)
void test_deque_insert_range__null_deque_container(void** state);
void test_deque_insert_range__non_inited(void** state);
void test_deque_insert_range__invalid_position(void** state);
void test_deque_insert_range__invalid_range(void** state);
void test_deque_insert_range__invalid_range_not_same_type(void** state);
void test_deque_insert_range__valid_range_belong_to_deque(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_empty_begin(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_empty_middle(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_empty_end(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_begin(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_middle(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_end(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_insert_full(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_front_elembefore_greater_equal_n(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_front_elembefore_less_n(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_back_elemafter_greater_n(void** state);
void test_deque_insert_range__valid_range_belong_to_deque_back_elemafter_less_equal_n(void** state);
void test_deque_insert_range__empty_insert_0(void** state);
void test_deque_insert_range__empty_insert_10(void** state);
void test_deque_insert_range__begin_insert_0(void** state);
void test_deque_insert_range__begin_insert_10(void** state);
void test_deque_insert_range__middle_insert_0(void** state);
void test_deque_insert_range__middle_insert_10(void** state);
void test_deque_insert_range__end_insert_0(void** state);
void test_deque_insert_range__end_insert_10(void** state);
void test_deque_insert_range__other_container_range(void** state);
void test_deque_insert_range__other_container_range1(void** state);
/*
 * test deque_insert_array
 */
UT_CASE_DECLARATION(deque_insert_array)
void test_deque_insert_array__null_deque_container(void** state);
void test_deque_insert_array__non_inited(void** state);
void test_deque_insert_array__invalid_position(void** state);
void test_deque_insert_array__invalid_array(void** state);
void test_deque_insert_array__empty_insert_0(void** state);
void test_deque_insert_array__empty_insert_10(void** state);
void test_deque_insert_array__begin_insert_0(void** state);
void test_deque_insert_array__begin_insert_10(void** state);
void test_deque_insert_array__middle_insert_0(void** state);
void test_deque_insert_array__middle_insert_10(void** state);
void test_deque_insert_array__end_insert_0(void** state);
void test_deque_insert_array__end_insert_10(void** state);
void test_deque_insert_array__other_container_array(void** state);
void test_deque_insert_array__other_container_array1(void** state);
void test_deque_insert_array__cstr(void** state);
void test_deque_insert_array__user_define(void** state);
/*
 * test deque_erase
 */
UT_CASE_DECLARATION(deque_erase)
void test_deque_erase__null_deque_container(void** state);
void test_deque_erase__non_inited_deque_container(void** state);
void test_deque_erase__invalid_pos_end(void** state);
void test_deque_erase__invalid_pos(void** state);
void test_deque_erase__successfully_begin(void** state);
void test_deque_erase__successfully_middle(void** state);
void test_deque_erase__successfully_back(void** state);
/*
 * test deque_erase_range
 */
UT_CASE_DECLARATION(deque_erase_range)
void test_deque_erase_range__null_deque_container(void** state);
void test_deque_erase_range__non_inited_deque_container(void** state);
void test_deque_erase_range__invalid_range_not_belong_to_deque(void** state);
void test_deque_erase_range__invalid_range(void** state);
void test_deque_erase_range__successfully_empty(void** state);
void test_deque_erase_range__successfully_begin(void** state);
void test_deque_erase_range__successfully_middle(void** state);
void test_deque_erase_range__successfully_end(void** state);
void test_deque_erase_range__successfully_all(void** state);
/*
 * test deque_clear
 */
UT_CASE_DECLARATION(deque_clear)
void test_deque_clear__null_deque_container(void** state);
void test_deque_clear__non_inited_deque_container(void** state);
void test_deque_clear__empty_deque_container(void** state);
void test_deque_clear__non_empty_deque_container(void** state);
/*
 * test deque_resize
 */
UT_CASE_DECLARATION(deque_resize)
void test_deque_resize__null_deque_container(void** state);
void test_deque_resize__non_inited(void** state);
void test_deque_resize__successfully_0_resize_0(void** state);
void test_deque_resize__successfully_0_resize_10(void** state);
void test_deque_resize__successfully_10_resize_0(void** state);
void test_deque_resize__successfully_10_resize_10(void** state);
void test_deque_resize__successfully_10_resize_1000(void** state);

#define UT_CSTL_DEQUE_CASE\
    UT_SUIT_BEGIN(cstl_deque, test_deque_init__null_deque_container),\
    UT_CASE(test_deque_init__non_created_deque_container),\
    UT_CASE(test_deque_init__successfully),\
    UT_CASE_BEGIN(deque_init_n, test_deque_init_n__null_deque_container),\
    UT_CASE(test_deque_init_n__non_created_deque_container),\
    UT_CASE(test_deque_init_n__empty),\
    UT_CASE(test_deque_init_n__c_builtin),\
    UT_CASE(test_deque_init_n__cstr),\
    UT_CASE(test_deque_init_n__libcstl_builtin),\
    UT_CASE(test_deque_init_n__user_define),\
    UT_CASE(test_deque_init_n__one_chunk),\
    UT_CASE(test_deque_init_n__more_than_one_chunk),\
    UT_CASE(test_deque_init_n__map_grow),\
    UT_CASE_BEGIN(deque_init_copy, test_deque_init_copy__null_dest_deque_container),\
    UT_CASE(test_deque_init_copy__null_src_deque_container),\
    UT_CASE(test_deque_init_copy__non_created_dest_deque_container),\
    UT_CASE(test_deque_init_copy__non_inited_src_deque_container),\
    UT_CASE(test_deque_init_copy__not_same_type),\
    UT_CASE(test_deque_init_copy__init_copy_empty),\
    UT_CASE(test_deque_init_copy__c_builtin),\
    UT_CASE(test_deque_init_copy__cstr),\
    UT_CASE(test_deque_init_copy__libcstl_builtin),\
    UT_CASE(test_deque_init_copy__user_define),\
    UT_CASE_BEGIN(deque_init_copy_range, test_deque_init_copy_range__null_deque_container),\
    UT_CASE(test_deque_init_copy_range__non_created_deque_container),\
    UT_CASE(test_deque_init_copy_range__invalid_range),\
    UT_CASE(test_deque_init_copy_range__not_same),\
    UT_CASE(test_deque_init_copy_range__init_copy_range_empty),\
    UT_CASE(test_deque_init_copy_range__c_builtin),\
    UT_CASE(test_deque_init_copy_range__cstr),\
    UT_CASE(test_deque_init_copy_range__libcstl_builtin),\
    UT_CASE(test_deque_init_copy_range__user_define),\
    UT_CASE(test_deque_init_copy_range__other_container_range),\
    UT_CASE(test_deque_init_copy_range__other_container_range_1),\
    UT_CASE_BEGIN(deque_init_copy_array, test_deque_init_copy_array__null_deque_container),\
    UT_CASE(test_deque_init_copy_array__non_created_deque_container),\
    UT_CASE(test_deque_init_copy_array__null_array),\
    UT_CASE(test_deque_init_copy_array__init_copy_array_empty),\
    UT_CASE(test_deque_init_copy_array__c_builtin),\
    UT_CASE(test_deque_init_copy_array__cstr),\
    UT_CASE(test_deque_init_copy_array__libcstl_builtin),\
    UT_CASE(test_deque_init_copy_array__user_define),\
    UT_CASE(test_deque_init_copy_array__other_container_array_1),\
    UT_CASE_BEGIN(deque_destroy, test_deque_destroy__null_deque_container),\
    UT_CASE(test_deque_destroy__non_created_deque_container),\
    UT_CASE(test_deque_destroy__created_non_inited),\
    UT_CASE(test_deque_destroy__empty),\
    UT_CASE(test_deque_destroy__non_empty),\
    UT_CASE_BEGIN(deque_size, test_deque_size__null_deque_container),\
    UT_CASE(test_deque_size__non_inited_deque_container),\
    UT_CASE(test_deque_size__empty),\
    UT_CASE(test_deque_size__non_empty),\
    UT_CASE_BEGIN(deque_empty, test_deque_empty__null_deque_container),\
    UT_CASE(test_deque_empty__non_inited_deque_container),\
    UT_CASE(test_deque_empty__empty),\
    UT_CASE(test_deque_empty__non_empty),\
    UT_CASE_BEGIN(deque_max_size, test_deque_max_size__null_deque_container),\
    UT_CASE(test_deque_max_size__non_inited_deque_container),\
    UT_CASE(test_deque_max_size__empty),\
    UT_CASE(test_deque_max_size__non_empty),\
    UT_CASE_BEGIN(deque_begin, test_deque_begin__null_deque_container),\
    UT_CASE(test_deque_begin__non_inited_deque_container),\
    UT_CASE(test_deque_begin__empty),\
    UT_CASE(test_deque_begin__non_empty),\
    UT_CASE_BEGIN(deque_end, test_deque_end__null_deque_container),\
    UT_CASE(test_deque_end__non_inited_deque_container),\
    UT_CASE(test_deque_end__empty),\
    UT_CASE(test_deque_end__non_empty),\
    UT_CASE_BEGIN(deque_assign, test_deque_assign__null_dest),\
    UT_CASE(test_deque_assign__null_src),\
    UT_CASE(test_deque_assign__non_inited_dest),\
    UT_CASE(test_deque_assign__non_inited_src),\
    UT_CASE(test_deque_assign__not_same_type),\
    UT_CASE(test_deque_assign__same_container),\
    UT_CASE(test_deque_assign__0_assign_0),\
    UT_CASE(test_deque_assign__0_assign_10),\
    UT_CASE(test_deque_assign__10_assign_0),\
    UT_CASE(test_deque_assign__10_assign_10_deque_equal),\
    UT_CASE(test_deque_assign__10_assign_10_deque_not_equal),\
    UT_CASE(test_deque_assign__10_assign_1000),\
    UT_CASE_BEGIN(deque_assign_range, test_deque_assign_range__null_deque_container),\
    UT_CASE(test_deque_assign_range__non_inited),\
    UT_CASE(test_deque_assign_range__invalid_it_begin),\
    UT_CASE(test_deque_assign_range__invalid_it_end),\
    UT_CASE(test_deque_assign_range__invalid_range),\
    UT_CASE(test_deque_assign_range__invalid_range_not_same_type),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_begin),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_end),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_front),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_middle),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_back),\
    UT_CASE(test_deque_assign_range__range_belong_to_deque_not_empty_full),\
    UT_CASE(test_deque_assign_range__0_assign_range_0),\
    UT_CASE(test_deque_assign_range__0_assign_range_10),\
    UT_CASE(test_deque_assign_range__10_assign_range_0),\
    UT_CASE(test_deque_assign_range__10_assign_range_10_same_elem),\
    UT_CASE(test_deque_assign_range__10_assign_range_10_not_same_elem),\
    UT_CASE(test_deque_assign_range__10_assign_range_1000),\
    UT_CASE(test_deque_assign_range__other_container_range),\
    UT_CASE(test_deque_assign_range__other_container_range1),\
    UT_CASE_BEGIN(deque_assign_array, test_deque_assign_array__null_deque_container),\
    UT_CASE(test_deque_assign_array__non_inited),\
    UT_CASE(test_deque_assign_array__null_array),\
    UT_CASE(test_deque_assign_array__0_assign_array_0),\
    UT_CASE(test_deque_assign_array__0_assign_array_10),\
    UT_CASE(test_deque_assign_array__10_assign_array_0),\
    UT_CASE(test_deque_assign_array__10_assign_array_10_same_elem),\
    UT_CASE(test_deque_assign_array__10_assign_array_10_not_same_elem),\
    UT_CASE(test_deque_assign_array__10_assign_array_1000),\
    UT_CASE(test_deque_assign_array__other_container_array),\
    UT_CASE(test_deque_assign_array__user_define),\
    UT_CASE(test_deque_assign_array__cstr),\
    UT_CASE_BEGIN(deque_equal, test_deque_equal__null_first),\
    UT_CASE(test_deque_equal__null_second),\
    UT_CASE(test_deque_equal__non_inited_first),\
    UT_CASE(test_deque_equal__non_inited_second),\
    UT_CASE(test_deque_equal__not_same_type),\
    UT_CASE(test_deque_equal__same_deque),\
    UT_CASE(test_deque_equal__size_first_less_than_second),\
    UT_CASE(test_deque_equal__size_first_greater_than_second),\
    UT_CASE(test_deque_equal__size_equal_0),\
    UT_CASE(test_deque_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_not_equal, test_deque_not_equal__null_first),\
    UT_CASE(test_deque_not_equal__null_second),\
    UT_CASE(test_deque_not_equal__non_inited_first),\
    UT_CASE(test_deque_not_equal__non_inited_second),\
    UT_CASE(test_deque_not_equal__not_same_type),\
    UT_CASE(test_deque_not_equal__same_deque),\
    UT_CASE(test_deque_not_equal__size_first_less_than_second),\
    UT_CASE(test_deque_not_equal__size_first_greater_than_second),\
    UT_CASE(test_deque_not_equal__size_equal_0),\
    UT_CASE(test_deque_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_less, test_deque_less__null_first),\
    UT_CASE(test_deque_less__null_second),\
    UT_CASE(test_deque_less__non_inited_first),\
    UT_CASE(test_deque_less__non_inited_second),\
    UT_CASE(test_deque_less__not_same_type),\
    UT_CASE(test_deque_less__same_deque),\
    UT_CASE(test_deque_less__size_first_less_than_second),\
    UT_CASE(test_deque_less__size_first_greater_than_second),\
    UT_CASE(test_deque_less__size_equal_0),\
    UT_CASE(test_deque_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_less_equal, test_deque_less_equal__null_first),\
    UT_CASE(test_deque_less_equal__null_second),\
    UT_CASE(test_deque_less_equal__non_inited_first),\
    UT_CASE(test_deque_less_equal__non_inited_second),\
    UT_CASE(test_deque_less_equal__not_same_type),\
    UT_CASE(test_deque_less_equal__same_deque),\
    UT_CASE(test_deque_less_equal__size_first_less_than_second),\
    UT_CASE(test_deque_less_equal__size_first_greater_than_second),\
    UT_CASE(test_deque_less_equal__size_equal_0),\
    UT_CASE(test_deque_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_greater, test_deque_greater__null_first),\
    UT_CASE(test_deque_greater__null_second),\
    UT_CASE(test_deque_greater__non_inited_first),\
    UT_CASE(test_deque_greater__non_inited_second),\
    UT_CASE(test_deque_greater__not_same_type),\
    UT_CASE(test_deque_greater__same_deque),\
    UT_CASE(test_deque_greater__size_first_less_than_second),\
    UT_CASE(test_deque_greater__size_first_greater_than_second),\
    UT_CASE(test_deque_greater__size_equal_0),\
    UT_CASE(test_deque_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_greater_equal, test_deque_greater_equal__null_first),\
    UT_CASE(test_deque_greater_equal__null_second),\
    UT_CASE(test_deque_greater_equal__non_inited_first),\
    UT_CASE(test_deque_greater_equal__non_inited_second),\
    UT_CASE(test_deque_greater_equal__not_same_type),\
    UT_CASE(test_deque_greater_equal__same_deque),\
    UT_CASE(test_deque_greater_equal__size_first_less_than_second),\
    UT_CASE(test_deque_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_deque_greater_equal__size_equal_0),\
    UT_CASE(test_deque_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_deque_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_deque_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(deque_at, test_deque_at__null_deque_container),\
    UT_CASE(test_deque_at__non_inited_deque_container),\
    UT_CASE(test_deque_at__invalid_subscript_empty),\
    UT_CASE(test_deque_at__invalid_subscript_end),\
    UT_CASE(test_deque_at__invalid_subscript),\
    UT_CASE(test_deque_at__successfully),\
    UT_CASE(test_deque_at__successfully_cstr),\
    UT_CASE_BEGIN(deque_front, test_deque_front__null_deque_container),\
    UT_CASE(test_deque_front__non_inited_deque_container),\
    UT_CASE(test_deque_front__empty),\
    UT_CASE(test_deque_front__successfully),\
    UT_CASE(test_deque_front__successfully_cstr),\
    UT_CASE_BEGIN(deque_back, test_deque_back__null_deque_container),\
    UT_CASE(test_deque_back__non_inited_deque_container),\
    UT_CASE(test_deque_back__empty),\
    UT_CASE(test_deque_back__successfully),\
    UT_CASE(test_deque_back__successfully_cstr),\
    UT_CASE_BEGIN(deque_swap, test_deque_swap__null_first),\
    UT_CASE(test_deque_swap__null_second),\
    UT_CASE(test_deque_swap__non_inited_first),\
    UT_CASE(test_deque_swap__non_inited_second),\
    UT_CASE(test_deque_swap__not_same_type),\
    UT_CASE(test_deque_swap__deque_equal),\
    UT_CASE(test_deque_swap__0_swap_10),\
    UT_CASE(test_deque_swap__10_swap_0),\
    UT_CASE(test_deque_swap__10_swap_10),\
    UT_CASE(test_deque_swap__10_swap_1000),\
    UT_CASE_BEGIN(deque_pop_back, test_deque_pop_back__null_deque_container),\
    UT_CASE(test_deque_pop_back__non_inited_deque_container),\
    UT_CASE(test_deque_pop_back__empty),\
    UT_CASE(test_deque_pop_back__successfully),\
    UT_CASE_BEGIN(deque_pop_front, test_deque_pop_front__null_deque_container),\
    UT_CASE(test_deque_pop_front__non_inited_deque_container),\
    UT_CASE(test_deque_pop_front__empty),\
    UT_CASE(test_deque_pop_front__successfully),\
    UT_CASE_BEGIN(deque_insert_range, test_deque_insert_range__null_deque_container),\
    UT_CASE(test_deque_insert_range__non_inited),\
    UT_CASE(test_deque_insert_range__invalid_position),\
    UT_CASE(test_deque_insert_range__invalid_range),\
    UT_CASE(test_deque_insert_range__invalid_range_not_same_type),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_empty_begin),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_empty_middle),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_empty_end),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_begin),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_middle),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_not_empty_end),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_insert_full),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_front_elembefore_greater_equal_n),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_front_elembefore_less_n),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_back_elemafter_greater_n),\
    UT_CASE(test_deque_insert_range__valid_range_belong_to_deque_back_elemafter_less_equal_n),\
    UT_CASE(test_deque_insert_range__empty_insert_0),\
    UT_CASE(test_deque_insert_range__empty_insert_10),\
    UT_CASE(test_deque_insert_range__begin_insert_0),\
    UT_CASE(test_deque_insert_range__begin_insert_10),\
    UT_CASE(test_deque_insert_range__middle_insert_0),\
    UT_CASE(test_deque_insert_range__middle_insert_10),\
    UT_CASE(test_deque_insert_range__end_insert_0),\
    UT_CASE(test_deque_insert_range__end_insert_10),\
    UT_CASE(test_deque_insert_range__other_container_range),\
    UT_CASE(test_deque_insert_range__other_container_range1),\
    UT_CASE_BEGIN(deque_insert_array, test_deque_insert_array__null_deque_container),\
    UT_CASE(test_deque_insert_array__non_inited),\
    UT_CASE(test_deque_insert_array__invalid_position),\
    UT_CASE(test_deque_insert_array__invalid_array),\
    UT_CASE(test_deque_insert_array__empty_insert_0),\
    UT_CASE(test_deque_insert_array__empty_insert_10),\
    UT_CASE(test_deque_insert_array__begin_insert_0),\
    UT_CASE(test_deque_insert_array__begin_insert_10),\
    UT_CASE(test_deque_insert_array__middle_insert_0),\
    UT_CASE(test_deque_insert_array__middle_insert_10),\
    UT_CASE(test_deque_insert_array__end_insert_0),\
    UT_CASE(test_deque_insert_array__end_insert_10),\
    UT_CASE(test_deque_insert_array__other_container_array),\
    UT_CASE(test_deque_insert_array__other_container_array1),\
    UT_CASE(test_deque_insert_array__cstr),\
    UT_CASE(test_deque_insert_array__user_define),\
    UT_CASE_BEGIN(deque_erase, test_deque_erase__null_deque_container),\
    UT_CASE(test_deque_erase__non_inited_deque_container),\
    UT_CASE(test_deque_erase__invalid_pos_end),\
    UT_CASE(test_deque_erase__invalid_pos),\
    UT_CASE(test_deque_erase__successfully_begin),\
    UT_CASE(test_deque_erase__successfully_middle),\
    UT_CASE(test_deque_erase__successfully_back),\
    UT_CASE_BEGIN(deque_erase_range, test_deque_erase_range__null_deque_container),\
    UT_CASE(test_deque_erase_range__non_inited_deque_container),\
    UT_CASE(test_deque_erase_range__invalid_range_not_belong_to_deque),\
    UT_CASE(test_deque_erase_range__invalid_range),\
    UT_CASE(test_deque_erase_range__successfully_empty),\
    UT_CASE(test_deque_erase_range__successfully_begin),\
    UT_CASE(test_deque_erase_range__successfully_middle),\
    UT_CASE(test_deque_erase_range__successfully_end),\
    UT_CASE(test_deque_erase_range__successfully_all),\
    UT_CASE_BEGIN(deque_clear, test_deque_clear__null_deque_container),\
    UT_CASE(test_deque_clear__non_inited_deque_container),\
    UT_CASE(test_deque_clear__empty_deque_container),\
    UT_CASE(test_deque_clear__non_empty_deque_container),\
    UT_CASE_BEGIN(deque_resize, test_deque_resize__null_deque_container),\
    UT_CASE(test_deque_resize__non_inited),\
    UT_CASE(test_deque_resize__successfully_0_resize_0),\
    UT_CASE(test_deque_resize__successfully_0_resize_10),\
    UT_CASE(test_deque_resize__successfully_10_resize_0),\
    UT_CASE(test_deque_resize__successfully_10_resize_10),\
    UT_CASE(test_deque_resize__successfully_10_resize_1000)

#endif /* _UT_CSTL_DEQUE_H_ */

