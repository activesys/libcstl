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
    UT_CASE(test_slist_insert_after_range__end_insert_10)

#endif /* _UT_CSTL_SLIST_H_ */

