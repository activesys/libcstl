#ifndef _UT_CSTL_VECTOR_H_
#define _UT_CSTL_VECTOR_H_

UT_SUIT_DECLARATION(cstl_vector)

/*
 * test vector_init
 */
UT_CASE_DECLARATION(vector_init)
void test_vector_init__null_vector_container(void** state);
void test_vector_init__non_created(void** state);
void test_vector_init__successfully_c_builtin(void** state);
void test_vector_init__successfully_cstl_builtin(void** state);
void test_vector_init__successfully_cstr(void** state);
void test_vector_init__successfully_user_defined(void** state);
/*
 * test vector_init_n
 */
UT_CASE_DECLARATION(vector_init_n)
void test_vector_init_n__null_vector_container(void** state);
void test_vector_init_n__non_created(void** state);
void test_vector_init_n__successfully_0(void** state);
void test_vector_init_n__successfully_c_builtin(void** state);
void test_vector_init_n__successfully_cstr(void** state);
void test_vector_init_n__successfully_cstl_builtin(void** state);
void test_vector_init_n__successfully_user_defined(void** state);
/*
 * test vector_init_copy
 */
UT_CASE_DECLARATION(vector_init_copy)
void test_vector_init_copy__null_dest(void** state);
void test_vector_init_copy__null_src(void** state);
void test_vector_init_copy__non_create_dest(void** state);
void test_vector_init_copy__non_inited_src(void** state);
void test_vector_init_copy__not_same_type(void** state);
void test_vector_init_copy__successfully_c_builtin_empty(void** state);
void test_vector_init_copy__successfully_c_builtin_little(void** state);
void test_vector_init_copy__successfully_c_builtin_huge(void** state);
void test_vector_init_copy__successfully_cstr_empty(void** state);
void test_vector_init_copy__successfully_cstr_little(void** state);
void test_vector_init_copy__successfully_cstr_huge(void** state);
void test_vector_init_copy__successfully_cstl_builtin_empty(void** state);
void test_vector_init_copy__successfully_cstl_builtin_little(void** state);
void test_vector_init_copy__successfully_cstl_builtin_huge(void** state);
void test_vector_init_copy__successfully_user_define_empty(void** state);
void test_vector_init_copy__successfully_user_define_little(void** state);
void test_vector_init_copy__successfully_user_define_huge(void** state);
/*
 * test vector_init_copy_range
 */
UT_CASE_DECLARATION(vector_init_copy_range)
void test_vector_init_copy_range__null_dest(void** state);
void test_vector_init_copy_range__invalid_begin_iterator(void** state);
void test_vector_init_copy_range__invalid_end_iterator(void** state);
void test_vector_init_copy_range__invalid_range(void** state);
void test_vector_init_copy_range__not_same_type(void** state);
void test_vector_init_copy_range__successfully_empty_range(void** state);
void test_vector_init_copy_range__successfully_c_builtin(void** state);
void test_vector_init_copy_range__successfully_cstr(void** state);
void test_vector_init_copy_range__successfully_cstl_builtin(void** state);
void test_vector_init_copy_range__successfully_user_define(void** state);
void test_vector_init_copy_range__other_container_range(void** state);
/*
 * test vector_init_copy_array
 */
UT_CASE_DECLARATION(vector_init_copy_array)
void test_vector_init_copy_array__null_dest(void** state);
void test_vector_init_copy_array__invalid_array(void** state);
void test_vector_init_copy_array__successfully_empty_array(void** state);
void test_vector_init_copy_array__successfully_c_builtin(void** state);
void test_vector_init_copy_array__successfully_cstr(void** state);
void test_vector_init_copy_array__successfully_cstl_builtin(void** state);
void test_vector_init_copy_array__successfully_user_define(void** state);
/*
 * test vector_destroy
 */
UT_CASE_DECLARATION(vector_destroy)
void test_vector_destroy__null_vector_container(void** state);
void test_vector_destroy__non_created(void** state);
void test_vector_destroy__created_non_inited(void** state);
void test_vector_destroy__inited_empty(void** state);
void test_vector_destroy__inited_non_empty(void** state);
/*
 * test vector_size
 */
UT_CASE_DECLARATION(vector_size)
void test_vector_size__null_vector_container(void** state);
void test_vector_size__non_inited(void** state);
void test_vector_size__successfully_empty(void** state);
void test_vector_size__successfully_non_empty(void** state);
/*
 * test vector_empty
 */
UT_CASE_DECLARATION(vector_empty)
void test_vector_empty__null_vector_container(void** state);
void test_vector_empty__non_inited(void** state);
void test_vector_empty__successfully_empty(void** state);
void test_vector_empty__successfully_non_empty(void** state);
/*
 * test vector_max_size
 */
UT_CASE_DECLARATION(vector_max_size)
void test_vector_max_size__null_vector_container(void** state);
void test_vector_max_size__non_inited(void** state);
void test_vector_max_size__successfully(void** state);
/*
 * test vector_capacity
 */
UT_CASE_DECLARATION(vector_capacity)
void test_vector_capacity__null_vector_container(void** state);
void test_vector_capacity__non_inited(void** state);
void test_vector_capacity__successfully_empty(void** state);
void test_vector_capacity__successfully_little(void** state);
void test_vector_capacity__successfully_huge(void** state);
/*
 * test vector_reserve
 */
UT_CASE_DECLARATION(vector_reserve)
void test_vector_reserve__null_vector_container(void** state);
void test_vector_reserve__non_inited(void** state);
void test_vector_reserve__shrink(void** state);
void test_vector_reserve__not_change(void** state);
void test_vector_reserve__expand(void** state);
/*
 * test vector_equal
 */
UT_CASE_DECLARATION(vector_equal)
void test_vector_equal__null_first(void** state);
void test_vector_equal__null_second(void** state);
void test_vector_equal__non_inited_first(void** state);
void test_vector_equal__non_inited_second(void** state);
void test_vector_equal__not_same_type(void** state);
void test_vector_equal__same_vector(void** state);
void test_vector_equal__size_first_less_than_second(void** state);
void test_vector_equal__size_first_greater_than_second(void** state);
void test_vector_equal__size_equal_0(void** state);
void test_vector_equal__size_equal_elem_first_less_than_second(void** state);
void test_vector_equal__size_equal_elem_first_greater_than_second(void** state);
void test_vector_equal__size_equal_elem_equal(void** state);
/*
 * test vector_not_equal
 */
UT_CASE_DECLARATION(vector_not_equal)
void test_vector_not_equal__null_first(void** state);
void test_vector_not_equal__null_second(void** state);
void test_vector_not_equal__non_inited_first(void** state);
void test_vector_not_equal__non_inited_second(void** state);
void test_vector_not_equal__not_same_type(void** state);
void test_vector_not_equal__same_vector(void** state);
void test_vector_not_equal__size_first_less_than_second(void** state);
void test_vector_not_equal__size_first_greater_than_second(void** state);
void test_vector_not_equal__size_equal_0(void** state);
void test_vector_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_vector_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_vector_not_equal__size_equal_elem_equal(void** state);
/*
 * test vector_less
 */
UT_CASE_DECLARATION(vector_less)
void test_vector_less__null_first(void** state);
void test_vector_less__null_second(void** state);
void test_vector_less__non_inited_first(void** state);
void test_vector_less__non_inited_second(void** state);
void test_vector_less__not_same_type(void** state);
void test_vector_less__same_vector(void** state);
void test_vector_less__size_first_less_than_second(void** state);
void test_vector_less__size_first_greater_than_second(void** state);
void test_vector_less__size_equal_0(void** state);
void test_vector_less__size_equal_elem_first_less_than_second(void** state);
void test_vector_less__size_equal_elem_first_greater_than_second(void** state);
void test_vector_less__size_equal_elem_equal(void** state);
/*
 * test vector_less_equal
 */
UT_CASE_DECLARATION(vector_less_equal)
void test_vector_less_equal__null_first(void** state);
void test_vector_less_equal__null_second(void** state);
void test_vector_less_equal__non_inited_first(void** state);
void test_vector_less_equal__non_inited_second(void** state);
void test_vector_less_equal__not_same_type(void** state);
void test_vector_less_equal__same_vector(void** state);
void test_vector_less_equal__size_first_less_than_second(void** state);
void test_vector_less_equal__size_first_greater_than_second(void** state);
void test_vector_less_equal__size_equal_0(void** state);
void test_vector_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_vector_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_vector_less_equal__size_equal_elem_equal(void** state);
/*
 * test vector_greater
 */
UT_CASE_DECLARATION(vector_greater)
void test_vector_greater__null_first(void** state);
void test_vector_greater__null_second(void** state);
void test_vector_greater__non_inited_first(void** state);
void test_vector_greater__non_inited_second(void** state);
void test_vector_greater__not_same_type(void** state);
void test_vector_greater__same_vector(void** state);
void test_vector_greater__size_first_less_than_second(void** state);
void test_vector_greater__size_first_greater_than_second(void** state);
void test_vector_greater__size_equal_0(void** state);
void test_vector_greater__size_equal_elem_first_less_than_second(void** state);
void test_vector_greater__size_equal_elem_first_greater_than_second(void** state);
void test_vector_greater__size_equal_elem_equal(void** state);
/*
 * test vector_greater_equal
 */
UT_CASE_DECLARATION(vector_greater_equal)
void test_vector_greater_equal__null_first(void** state);
void test_vector_greater_equal__null_second(void** state);
void test_vector_greater_equal__non_inited_first(void** state);
void test_vector_greater_equal__non_inited_second(void** state);
void test_vector_greater_equal__not_same_type(void** state);
void test_vector_greater_equal__same_vector(void** state);
void test_vector_greater_equal__size_first_less_than_second(void** state);
void test_vector_greater_equal__size_first_greater_than_second(void** state);
void test_vector_greater_equal__size_equal_0(void** state);
void test_vector_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_vector_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_vector_greater_equal__size_equal_elem_equal(void** state);
/*
 * test vector_assign
 */
UT_CASE_DECLARATION(vector_assign)
void test_vector_assign__null_dest(void** state);
void test_vector_assign__null_src(void** state);
void test_vector_assign__non_inited_dest(void** state);
void test_vector_assign__non_inited_src(void** state);
void test_vector_assign__not_same_type(void** state);
void test_vector_assign__same_container(void** state);
void test_vector_assign__0_assign_0(void** state);
void test_vector_assign__0_assign_10(void** state);
void test_vector_assign__0_assign_1000(void** state);
void test_vector_assign__10_assign_0(void** state);
void test_vector_assign__10_assign_10_vector_equal(void** state);
void test_vector_assign__10_assign_10_vector_not_equal(void** state);
void test_vector_assign__10_assign_1000(void** state);
void test_vector_assign__1000_assign_0(void** state);
void test_vector_assign__1000_assign_10(void** state);
void test_vector_assign__1000_assign_1010(void** state);
void test_vector_assign__1000_assign_1810(void** state);
/*
 * test vector_assign_range
 */
UT_CASE_DECLARATION(vector_assign_range)
void test_vector_assign_range__null_vector_container(void** state);
void test_vector_assign_range__non_inited(void** state);
void test_vector_assign_range__invalid_it_begin(void** state);
void test_vector_assign_range__invalid_it_end(void** state);
void test_vector_assign_range__invalid_range(void** state);
void test_vector_assign_range__invalid_range_not_same_type(void** state);
void test_vector_assign_range__range_belong_to_vector(void** state);
void test_vector_assign_range__0_assign_range_0(void** state);
void test_vector_assign_range__0_assign_range_10(void** state);
void test_vector_assign_range__0_assign_range_1000(void** state);
void test_vector_assign_range__10_assign_range_0(void** state);
void test_vector_assign_range__10_assign_range_10_same_elem(void** state);
void test_vector_assign_range__10_assign_range_10_not_same_elem(void** state);
void test_vector_assign_range__10_assign_range_1000(void** state);
void test_vector_assign_range__1000_assign_range_0(void** state);
void test_vector_assign_range__1000_assign_range_10(void** state);
void test_vector_assign_range__1000_assign_range_1700(void** state);
void test_vector_assign_range__other_container_range(void** state);
/*
 * test vector_assign_array
 */
UT_CASE_DECLARATION(vector_assign_array)
void test_vector_assign_array__null_vector_container(void** state);
void test_vector_assign_array__non_inited(void** state);
void test_vector_assign_array__invalid_array(void** state);
void test_vector_assign_array__0_assign_array_0(void** state);
void test_vector_assign_array__0_assign_array_10(void** state);
void test_vector_assign_array__0_assign_array_1000(void** state);
void test_vector_assign_array__10_assign_array_0(void** state);
void test_vector_assign_array__10_assign_array_10_same_elem(void** state);
void test_vector_assign_array__10_assign_array_10_not_same_elem(void** state);
void test_vector_assign_array__10_assign_array_1000(void** state);
void test_vector_assign_array__1000_assign_array_0(void** state);
void test_vector_assign_array__1000_assign_array_10(void** state);
void test_vector_assign_array__1000_assign_array_1700(void** state);
void test_vector_assign_array__cstr(void** state);
void test_vector_assign_array__cstl(void** state);
void test_vector_assign_array__user_define(void** state);
/*
 * test vector_swap
 */
UT_CASE_DECLARATION(vector_swap)
void test_vector_swap__null_first(void** state);
void test_vector_swap__null_second(void** state);
void test_vector_swap__non_inited_first(void** state);
void test_vector_swap__non_inited_second(void** state);
void test_vector_swap__not_same_type(void** state);
void test_vector_swap__vector_equal(void** state);
void test_vector_swap__0_swap_10(void** state);
void test_vector_swap__0_swap_1000(void** state);
void test_vector_swap__10_swap_0(void** state);
void test_vector_swap__10_swap_10(void** state);
void test_vector_swap__10_swap_1000(void** state);
void test_vector_swap__1000_swap_0(void** state);
void test_vector_swap__1000_swap_10(void** state);
void test_vector_swap__1000_swap_1010(void** state);
/*
 * test vector_at
 */
UT_CASE_DECLARATION(vector_at)
void test_vector_at__null_vector_container(void** state);
void test_vector_at__non_inited_vector_container(void** state);
void test_vector_at__invalid_subscript_empty(void** state);
void test_vector_at__invalid_subscript_end(void** state);
void test_vector_at__invalid_subscript(void** state);
void test_vector_at__successfully(void** state);
void test_vector_at__successfully_cstr(void** state);
/*
 * test vector_front
 */
UT_CASE_DECLARATION(vector_front)
void test_vector_front__null_vector_container(void** state);
void test_vector_front__non_inited_vector_container(void** state);
void test_vector_front__empty(void** state);
void test_vector_front__successfully(void** state);
void test_vector_front__successfully_cstr(void** state);
/*
 * test vector_back
 */
UT_CASE_DECLARATION(vector_back)
void test_vector_back__null_vector_container(void** state);
void test_vector_back__non_inited_vector_container(void** state);
void test_vector_back__empty(void** state);
void test_vector_back__successfully(void** state);
void test_vector_back__successfully_cstr(void** state);
/*
 * test vector_begin
 */
UT_CASE_DECLARATION(vector_begin)
void test_vector_begin__null_vector_container(void** state);
void test_vector_begin__non_inited_vector_container(void** state);
void test_vector_begin__empty(void** state);
void test_vector_begin__non_empty(void** state);
/*
 * test vector_end
 */
UT_CASE_DECLARATION(vector_end)
void test_vector_end__null_vector_container(void** state);
void test_vector_end__non_inited_vector_container(void** state);
void test_vector_end__empty(void** state);
void test_vector_end__non_empty(void** state);
/*
 * test vector_insert_range
 */
UT_CASE_DECLARATION(vector_insert_range)
void test_vector_insert_range__null_vector_container(void** state);
void test_vector_insert_range__non_inited(void** state);
void test_vector_insert_range__invalid_position(void** state);
void test_vector_insert_range__invalid_range(void** state);
void test_vector_insert_range__invalid_range_not_same_type(void** state);
void test_vector_insert_range__invalid_range_belong_to_vector(void** state);
void test_vector_insert_range__empty_insert_0(void** state);
void test_vector_insert_range__empty_insert_10(void** state);
void test_vector_insert_range__empty_insert_1000(void** state);
void test_vector_insert_range__begin_insert_0(void** state);
void test_vector_insert_range__begin_insert_10(void** state);
void test_vector_insert_range__begin_insert_1000(void** state);
void test_vector_insert_range__middle_insert_0(void** state);
void test_vector_insert_range__middle_insert_10(void** state);
void test_vector_insert_range__middle_insert_1000(void** state);
void test_vector_insert_range__end_insert_0(void** state);
void test_vector_insert_range__end_insert_10(void** state);
void test_vector_insert_range__end_insert_1000(void** state);
void test_vector_insert_range__other_container_range(void** state);
/*
 * test vector_insert_array
 */
UT_CASE_DECLARATION(vector_insert_array)
void test_vector_insert_array__null_vector_container(void** state);
void test_vector_insert_array__non_inited(void** state);
void test_vector_insert_array__invalid_position(void** state);
void test_vector_insert_array__invalid_array(void** state);
void test_vector_insert_array__empty_insert_0(void** state);
void test_vector_insert_array__empty_insert_10(void** state);
void test_vector_insert_array__empty_insert_1000(void** state);
void test_vector_insert_array__begin_insert_0(void** state);
void test_vector_insert_array__begin_insert_10(void** state);
void test_vector_insert_array__begin_insert_1000(void** state);
void test_vector_insert_array__middle_insert_0(void** state);
void test_vector_insert_array__middle_insert_10(void** state);
void test_vector_insert_array__middle_insert_1000(void** state);
void test_vector_insert_array__end_insert_0(void** state);
void test_vector_insert_array__end_insert_10(void** state);
void test_vector_insert_array__end_insert_1000(void** state);
void test_vector_insert_array__cstr(void** state);
void test_vector_insert_array__cstl(void** state);
void test_vector_insert_array__user_define(void** state);
/*
 * test vector_pop_back
 */
UT_CASE_DECLARATION(vector_pop_back)
void test_vector_pop_back__null_vector_container(void** state);
void test_vector_pop_back__non_inited_vector_container(void** state);
void test_vector_pop_back__empty(void** state);
void test_vector_pop_back__successfully(void** state);
/*
 * test vector_erase
 */
UT_CASE_DECLARATION(vector_erase)
void test_vector_erase__null_vector_container(void** state);
void test_vector_erase__non_inited_vector_container(void** state);
void test_vector_erase__invalid_pos_end(void** state);
void test_vector_erase__invalid_pos(void** state);
void test_vector_erase__successfully_begin(void** state);
void test_vector_erase__successfully_middle(void** state);
void test_vector_erase__successfully_back(void** state);
/*
 * test vector_erase_range
 */
UT_CASE_DECLARATION(vector_erase_range)
void test_vector_erase_range__null_vector_container(void** state);
void test_vector_erase_range__non_inited_vector_container(void** state);
void test_vector_erase_range__invalid_range_not_belong_to_vector(void** state);
void test_vector_erase_range__invalid_range(void** state);
void test_vector_erase_range__successfully_empty(void** state);
void test_vector_erase_range__successfully_begin(void** state);
void test_vector_erase_range__successfully_middle(void** state);
void test_vector_erase_range__successfully_end(void** state);
void test_vector_erase_range__successfully_all(void** state);
/*
 * test vector_clear
 */
UT_CASE_DECLARATION(vector_clear)
void test_vector_clear__null_vector_container(void** state);
void test_vector_clear__non_inited_vector_container(void** state);
void test_vector_clear__empty_vector_container(void** state);
void test_vector_clear__non_empty_vector_container(void** state);
/*
 * test vector_resize
 */
UT_CASE_DECLARATION(vector_resize)
void test_vector_resize__null_vector_container(void** state);
void test_vector_resize__non_inited(void** state);
void test_vector_resize__successfully_0_resize_0(void** state);
void test_vector_resize__successfully_0_resize_10(void** state);
void test_vector_resize__successfully_0_resize_1000(void** state);
void test_vector_resize__successfully_10_resize_0(void** state);
void test_vector_resize__successfully_10_resize_10(void** state);
void test_vector_resize__successfully_10_resize_1000(void** state);
void test_vector_resize__successfully_1000_resize_0(void** state);
void test_vector_resize__successfully_1000_resize_10(void** state);
void test_vector_resize__successfully_1000_resize_1000(void** state);
void test_vector_resize__successfully_1000_resize_1200(void** state);
void test_vector_resize__successfully_1000_resize_2000(void** state);

#define UT_CSTL_VECTOR_CASE\
    UT_SUIT_BEGIN(cstl_vector, test_vector_init__null_vector_container),\
    UT_CASE(test_vector_init__non_created),\
    UT_CASE(test_vector_init__successfully_c_builtin),\
    UT_CASE(test_vector_init__successfully_cstl_builtin),\
    UT_CASE(test_vector_init__successfully_cstr),\
    UT_CASE(test_vector_init__successfully_user_defined),\
    UT_CASE_BEGIN(vector_init_n, test_vector_init_n__null_vector_container),\
    UT_CASE(test_vector_init_n__non_created),\
    UT_CASE(test_vector_init_n__successfully_0),\
    UT_CASE(test_vector_init_n__successfully_c_builtin),\
    UT_CASE(test_vector_init_n__successfully_cstr),\
    UT_CASE(test_vector_init_n__successfully_cstl_builtin),\
    UT_CASE(test_vector_init_n__successfully_user_defined),\
    UT_CASE_BEGIN(vector_init_copy, test_vector_init_copy__null_dest),\
    UT_CASE(test_vector_init_copy__null_src),\
    UT_CASE(test_vector_init_copy__non_create_dest),\
    UT_CASE(test_vector_init_copy__non_inited_src),\
    UT_CASE(test_vector_init_copy__not_same_type),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_empty),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_little),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_huge),\
    UT_CASE(test_vector_init_copy__successfully_cstr_empty),\
    UT_CASE(test_vector_init_copy__successfully_cstr_little),\
    UT_CASE(test_vector_init_copy__successfully_cstr_huge),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_empty),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_little),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_huge),\
    UT_CASE(test_vector_init_copy__successfully_user_define_empty),\
    UT_CASE(test_vector_init_copy__successfully_user_define_little),\
    UT_CASE(test_vector_init_copy__successfully_user_define_huge),\
    UT_CASE_BEGIN(vector_init_copy_range, test_vector_init_copy_range__null_dest),\
    UT_CASE(test_vector_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_vector_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_vector_init_copy_range__invalid_range),\
    UT_CASE(test_vector_init_copy_range__not_same_type),\
    UT_CASE(test_vector_init_copy_range__successfully_empty_range),\
    UT_CASE(test_vector_init_copy_range__successfully_c_builtin),\
    UT_CASE(test_vector_init_copy_range__successfully_cstr),\
    UT_CASE(test_vector_init_copy_range__successfully_cstl_builtin),\
    UT_CASE(test_vector_init_copy_range__successfully_user_define),\
    UT_CASE(test_vector_init_copy_range__other_container_range),\
    UT_CASE_BEGIN(vector_init_copy_array, test_vector_init_copy_array__null_dest),\
    UT_CASE(test_vector_init_copy_array__invalid_array),\
    UT_CASE(test_vector_init_copy_array__successfully_empty_array),\
    UT_CASE(test_vector_init_copy_array__successfully_c_builtin),\
    UT_CASE(test_vector_init_copy_array__successfully_cstr),\
    UT_CASE(test_vector_init_copy_array__successfully_cstl_builtin),\
    UT_CASE(test_vector_init_copy_array__successfully_user_define),\
    UT_CASE_BEGIN(vector_destroy, test_vector_destroy__null_vector_container),\
    UT_CASE(test_vector_destroy__non_created),\
    UT_CASE(test_vector_destroy__created_non_inited),\
    UT_CASE(test_vector_destroy__inited_empty),\
    UT_CASE(test_vector_destroy__inited_non_empty),\
    UT_CASE_BEGIN(vector_size, test_vector_size__null_vector_container),\
    UT_CASE(test_vector_size__non_inited),\
    UT_CASE(test_vector_size__successfully_empty),\
    UT_CASE(test_vector_size__successfully_non_empty),\
    UT_CASE_BEGIN(vector_empty, test_vector_empty__null_vector_container),\
    UT_CASE(test_vector_empty__non_inited),\
    UT_CASE(test_vector_empty__successfully_empty),\
    UT_CASE(test_vector_empty__successfully_non_empty),\
    UT_CASE_BEGIN(vector_max_size, test_vector_max_size__null_vector_container),\
    UT_CASE(test_vector_max_size__non_inited),\
    UT_CASE(test_vector_max_size__successfully),\
    UT_CASE_BEGIN(vector_capacity, test_vector_capacity__null_vector_container),\
    UT_CASE(test_vector_capacity__non_inited),\
    UT_CASE(test_vector_capacity__successfully_empty),\
    UT_CASE(test_vector_capacity__successfully_little),\
    UT_CASE(test_vector_capacity__successfully_huge),\
    UT_CASE_BEGIN(vector_reserve, test_vector_reserve__null_vector_container),\
    UT_CASE(test_vector_reserve__non_inited),\
    UT_CASE(test_vector_reserve__shrink),\
    UT_CASE(test_vector_reserve__not_change),\
    UT_CASE(test_vector_reserve__expand),\
    UT_CASE_BEGIN(vector_equal, test_vector_equal__null_first),\
    UT_CASE(test_vector_equal__null_second),\
    UT_CASE(test_vector_equal__non_inited_first),\
    UT_CASE(test_vector_equal__non_inited_second),\
    UT_CASE(test_vector_equal__not_same_type),\
    UT_CASE(test_vector_equal__same_vector),\
    UT_CASE(test_vector_equal__size_first_less_than_second),\
    UT_CASE(test_vector_equal__size_first_greater_than_second),\
    UT_CASE(test_vector_equal__size_equal_0),\
    UT_CASE(test_vector_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_not_equal, test_vector_not_equal__null_first),\
    UT_CASE(test_vector_not_equal__null_second),\
    UT_CASE(test_vector_not_equal__non_inited_first),\
    UT_CASE(test_vector_not_equal__non_inited_second),\
    UT_CASE(test_vector_not_equal__not_same_type),\
    UT_CASE(test_vector_not_equal__same_vector),\
    UT_CASE(test_vector_not_equal__size_first_less_than_second),\
    UT_CASE(test_vector_not_equal__size_first_greater_than_second),\
    UT_CASE(test_vector_not_equal__size_equal_0),\
    UT_CASE(test_vector_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_less, test_vector_less__null_first),\
    UT_CASE(test_vector_less__null_second),\
    UT_CASE(test_vector_less__non_inited_first),\
    UT_CASE(test_vector_less__non_inited_second),\
    UT_CASE(test_vector_less__not_same_type),\
    UT_CASE(test_vector_less__same_vector),\
    UT_CASE(test_vector_less__size_first_less_than_second),\
    UT_CASE(test_vector_less__size_first_greater_than_second),\
    UT_CASE(test_vector_less__size_equal_0),\
    UT_CASE(test_vector_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_less_equal, test_vector_less_equal__null_first),\
    UT_CASE(test_vector_less_equal__null_second),\
    UT_CASE(test_vector_less_equal__non_inited_first),\
    UT_CASE(test_vector_less_equal__non_inited_second),\
    UT_CASE(test_vector_less_equal__not_same_type),\
    UT_CASE(test_vector_less_equal__same_vector),\
    UT_CASE(test_vector_less_equal__size_first_less_than_second),\
    UT_CASE(test_vector_less_equal__size_first_greater_than_second),\
    UT_CASE(test_vector_less_equal__size_equal_0),\
    UT_CASE(test_vector_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_greater, test_vector_greater__null_first),\
    UT_CASE(test_vector_greater__null_second),\
    UT_CASE(test_vector_greater__non_inited_first),\
    UT_CASE(test_vector_greater__non_inited_second),\
    UT_CASE(test_vector_greater__not_same_type),\
    UT_CASE(test_vector_greater__same_vector),\
    UT_CASE(test_vector_greater__size_first_less_than_second),\
    UT_CASE(test_vector_greater__size_first_greater_than_second),\
    UT_CASE(test_vector_greater__size_equal_0),\
    UT_CASE(test_vector_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_greater_equal, test_vector_greater_equal__null_first),\
    UT_CASE(test_vector_greater_equal__null_second),\
    UT_CASE(test_vector_greater_equal__non_inited_first),\
    UT_CASE(test_vector_greater_equal__non_inited_second),\
    UT_CASE(test_vector_greater_equal__not_same_type),\
    UT_CASE(test_vector_greater_equal__same_vector),\
    UT_CASE(test_vector_greater_equal__size_first_less_than_second),\
    UT_CASE(test_vector_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_vector_greater_equal__size_equal_0),\
    UT_CASE(test_vector_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_vector_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_vector_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(vector_assign, test_vector_assign__null_dest),\
    UT_CASE(test_vector_assign__null_src),\
    UT_CASE(test_vector_assign__non_inited_dest),\
    UT_CASE(test_vector_assign__non_inited_src),\
    UT_CASE(test_vector_assign__not_same_type),\
    UT_CASE(test_vector_assign__same_container),\
    UT_CASE(test_vector_assign__0_assign_0),\
    UT_CASE(test_vector_assign__0_assign_10),\
    UT_CASE(test_vector_assign__0_assign_1000),\
    UT_CASE(test_vector_assign__10_assign_0),\
    UT_CASE(test_vector_assign__10_assign_10_vector_equal),\
    UT_CASE(test_vector_assign__10_assign_10_vector_not_equal),\
    UT_CASE(test_vector_assign__10_assign_1000),\
    UT_CASE(test_vector_assign__1000_assign_0),\
    UT_CASE(test_vector_assign__1000_assign_10),\
    UT_CASE(test_vector_assign__1000_assign_1010),\
    UT_CASE(test_vector_assign__1000_assign_1810),\
    UT_CASE_BEGIN(vector_assign_range, test_vector_assign_range__null_vector_container),\
    UT_CASE(test_vector_assign_range__non_inited),\
    UT_CASE(test_vector_assign_range__invalid_it_begin),\
    UT_CASE(test_vector_assign_range__invalid_it_end),\
    UT_CASE(test_vector_assign_range__invalid_range),\
    UT_CASE(test_vector_assign_range__invalid_range_not_same_type),\
    UT_CASE(test_vector_assign_range__range_belong_to_vector),\
    UT_CASE(test_vector_assign_range__0_assign_range_0),\
    UT_CASE(test_vector_assign_range__0_assign_range_10),\
    UT_CASE(test_vector_assign_range__0_assign_range_1000),\
    UT_CASE(test_vector_assign_range__10_assign_range_0),\
    UT_CASE(test_vector_assign_range__10_assign_range_10_same_elem),\
    UT_CASE(test_vector_assign_range__10_assign_range_10_not_same_elem),\
    UT_CASE(test_vector_assign_range__10_assign_range_1000),\
    UT_CASE(test_vector_assign_range__1000_assign_range_0),\
    UT_CASE(test_vector_assign_range__1000_assign_range_10),\
    UT_CASE(test_vector_assign_range__1000_assign_range_1700),\
    UT_CASE(test_vector_assign_range__other_container_range),\
    UT_CASE_BEGIN(vector_assign_array, test_vector_assign_array__null_vector_container),\
    UT_CASE(test_vector_assign_array__non_inited),\
    UT_CASE(test_vector_assign_array__invalid_array),\
    UT_CASE(test_vector_assign_array__0_assign_array_0),\
    UT_CASE(test_vector_assign_array__0_assign_array_10),\
    UT_CASE(test_vector_assign_array__0_assign_array_1000),\
    UT_CASE(test_vector_assign_array__10_assign_array_0),\
    UT_CASE(test_vector_assign_array__10_assign_array_10_same_elem),\
    UT_CASE(test_vector_assign_array__10_assign_array_10_not_same_elem),\
    UT_CASE(test_vector_assign_array__10_assign_array_1000),\
    UT_CASE(test_vector_assign_array__1000_assign_array_0),\
    UT_CASE(test_vector_assign_array__1000_assign_array_10),\
    UT_CASE(test_vector_assign_array__1000_assign_array_1700),\
    UT_CASE(test_vector_assign_array__cstr),\
    UT_CASE(test_vector_assign_array__cstl),\
    UT_CASE(test_vector_assign_array__user_define),\
    UT_CASE_BEGIN(vector_swap, test_vector_swap__null_first),\
    UT_CASE(test_vector_swap__null_second),\
    UT_CASE(test_vector_swap__non_inited_first),\
    UT_CASE(test_vector_swap__non_inited_second),\
    UT_CASE(test_vector_swap__not_same_type),\
    UT_CASE(test_vector_swap__vector_equal),\
    UT_CASE(test_vector_swap__0_swap_10),\
    UT_CASE(test_vector_swap__0_swap_1000),\
    UT_CASE(test_vector_swap__10_swap_0),\
    UT_CASE(test_vector_swap__10_swap_10),\
    UT_CASE(test_vector_swap__10_swap_1000),\
    UT_CASE(test_vector_swap__1000_swap_0),\
    UT_CASE(test_vector_swap__1000_swap_10),\
    UT_CASE(test_vector_swap__1000_swap_1010),\
    UT_CASE_BEGIN(vector_at, test_vector_at__null_vector_container),\
    UT_CASE(test_vector_at__non_inited_vector_container),\
    UT_CASE(test_vector_at__invalid_subscript_empty),\
    UT_CASE(test_vector_at__invalid_subscript_end),\
    UT_CASE(test_vector_at__invalid_subscript),\
    UT_CASE(test_vector_at__successfully),\
    UT_CASE(test_vector_at__successfully_cstr),\
    UT_CASE_BEGIN(vector_front, test_vector_front__null_vector_container),\
    UT_CASE(test_vector_front__non_inited_vector_container),\
    UT_CASE(test_vector_front__empty),\
    UT_CASE(test_vector_front__successfully),\
    UT_CASE(test_vector_front__successfully_cstr),\
    UT_CASE_BEGIN(vector_back, test_vector_back__null_vector_container),\
    UT_CASE(test_vector_back__non_inited_vector_container),\
    UT_CASE(test_vector_back__empty),\
    UT_CASE(test_vector_back__successfully),\
    UT_CASE(test_vector_back__successfully_cstr),\
    UT_CASE_BEGIN(vector_begin, test_vector_begin__null_vector_container),\
    UT_CASE(test_vector_begin__non_inited_vector_container),\
    UT_CASE(test_vector_begin__empty),\
    UT_CASE(test_vector_begin__non_empty),\
    UT_CASE_BEGIN(vector_end, test_vector_end__null_vector_container),\
    UT_CASE(test_vector_end__non_inited_vector_container),\
    UT_CASE(test_vector_end__empty),\
    UT_CASE(test_vector_end__non_empty),\
    UT_CASE_BEGIN(vector_insert_range, test_vector_insert_range__null_vector_container),\
    UT_CASE(test_vector_insert_range__non_inited),\
    UT_CASE(test_vector_insert_range__invalid_position),\
    UT_CASE(test_vector_insert_range__invalid_range),\
    UT_CASE(test_vector_insert_range__invalid_range_not_same_type),\
    UT_CASE(test_vector_insert_range__invalid_range_belong_to_vector),\
    UT_CASE(test_vector_insert_range__empty_insert_0),\
    UT_CASE(test_vector_insert_range__empty_insert_10),\
    UT_CASE(test_vector_insert_range__empty_insert_1000),\
    UT_CASE(test_vector_insert_range__begin_insert_0),\
    UT_CASE(test_vector_insert_range__begin_insert_10),\
    UT_CASE(test_vector_insert_range__begin_insert_1000),\
    UT_CASE(test_vector_insert_range__middle_insert_0),\
    UT_CASE(test_vector_insert_range__middle_insert_10),\
    UT_CASE(test_vector_insert_range__middle_insert_1000),\
    UT_CASE(test_vector_insert_range__end_insert_0),\
    UT_CASE(test_vector_insert_range__end_insert_10),\
    UT_CASE(test_vector_insert_range__end_insert_1000),\
    UT_CASE(test_vector_insert_range__other_container_range),\
    UT_CASE_BEGIN(vector_insert_array, test_vector_insert_array__null_vector_container),\
    UT_CASE(test_vector_insert_array__non_inited),\
    UT_CASE(test_vector_insert_array__invalid_position),\
    UT_CASE(test_vector_insert_array__invalid_array),\
    UT_CASE(test_vector_insert_array__empty_insert_0),\
    UT_CASE(test_vector_insert_array__empty_insert_10),\
    UT_CASE(test_vector_insert_array__empty_insert_1000),\
    UT_CASE(test_vector_insert_array__begin_insert_0),\
    UT_CASE(test_vector_insert_array__begin_insert_10),\
    UT_CASE(test_vector_insert_array__begin_insert_1000),\
    UT_CASE(test_vector_insert_array__middle_insert_0),\
    UT_CASE(test_vector_insert_array__middle_insert_10),\
    UT_CASE(test_vector_insert_array__middle_insert_1000),\
    UT_CASE(test_vector_insert_array__end_insert_0),\
    UT_CASE(test_vector_insert_array__end_insert_10),\
    UT_CASE(test_vector_insert_array__end_insert_1000),\
    UT_CASE(test_vector_insert_array__cstr),\
    UT_CASE(test_vector_insert_array__cstl),\
    UT_CASE(test_vector_insert_array__user_define),\
    UT_CASE_BEGIN(vector_pop_back, test_vector_pop_back__null_vector_container),\
    UT_CASE(test_vector_pop_back__non_inited_vector_container),\
    UT_CASE(test_vector_pop_back__empty),\
    UT_CASE(test_vector_pop_back__successfully),\
    UT_CASE_BEGIN(vector_erase, test_vector_erase__null_vector_container),\
    UT_CASE(test_vector_erase__non_inited_vector_container),\
    UT_CASE(test_vector_erase__invalid_pos_end),\
    UT_CASE(test_vector_erase__invalid_pos),\
    UT_CASE(test_vector_erase__successfully_begin),\
    UT_CASE(test_vector_erase__successfully_middle),\
    UT_CASE(test_vector_erase__successfully_back),\
    UT_CASE_BEGIN(vector_erase_range, test_vector_erase_range__null_vector_container),\
    UT_CASE(test_vector_erase_range__non_inited_vector_container),\
    UT_CASE(test_vector_erase_range__invalid_range_not_belong_to_vector),\
    UT_CASE(test_vector_erase_range__invalid_range),\
    UT_CASE(test_vector_erase_range__successfully_empty),\
    UT_CASE(test_vector_erase_range__successfully_begin),\
    UT_CASE(test_vector_erase_range__successfully_middle),\
    UT_CASE(test_vector_erase_range__successfully_end),\
    UT_CASE(test_vector_erase_range__successfully_all),\
    UT_CASE_BEGIN(vector_clear, test_vector_clear__null_vector_container),\
    UT_CASE(test_vector_clear__non_inited_vector_container),\
    UT_CASE(test_vector_clear__empty_vector_container),\
    UT_CASE(test_vector_clear__non_empty_vector_container),\
    UT_CASE_BEGIN(vector_resize, test_vector_resize__null_vector_container),\
    UT_CASE(test_vector_resize__non_inited),\
    UT_CASE(test_vector_resize__successfully_0_resize_0),\
    UT_CASE(test_vector_resize__successfully_0_resize_10),\
    UT_CASE(test_vector_resize__successfully_0_resize_1000),\
    UT_CASE(test_vector_resize__successfully_10_resize_0),\
    UT_CASE(test_vector_resize__successfully_10_resize_10),\
    UT_CASE(test_vector_resize__successfully_10_resize_1000),\
    UT_CASE(test_vector_resize__successfully_1000_resize_0),\
    UT_CASE(test_vector_resize__successfully_1000_resize_10),\
    UT_CASE(test_vector_resize__successfully_1000_resize_1000),\
    UT_CASE(test_vector_resize__successfully_1000_resize_1200),\
    UT_CASE(test_vector_resize__successfully_1000_resize_2000)

#endif /* _UT_CSTL_VECTOR_H_ */

