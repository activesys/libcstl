#ifndef _UT_CSTL_LIST_AUX_H_
#define _UT_CSTL_LIST_AUX_H_

UT_SUIT_DECLARATION(cstl_list_aux)

/*
 * test _list_is_created
 */
UT_CASE_DECLARATION(_list_is_created)
void test__list_is_created__null_list_container(void** state);
void test__list_is_created__invalid_type_style(void** state);
void test__list_is_created__invalid_type_pointer(void** state);
void test__list_is_created__null_node(void** state);
void test__list_is_created__uninited_allocator(void** state);
void test__list_is_created__successfully(void** state);
/*
 * test _list_is_inited
 */
UT_CASE_DECLARATION(_list_is_inited)
void test__list_is_inited__null_list_container(void** state);
void test__list_is_inited__invalid_type_styple(void** state);
void test__list_is_inited__invalid_type_pointer(void** state);
void test__list_is_inited__null_node(void** state);
void test__list_is_inited__invalid_node_prev_pointer(void** state);
void test__list_is_inited__invalid_node_next_pointer(void** state);
void test__list_is_inited__init_empty(void** state);
void test__list_is_inited__init_non_empty(void** state);
/*
 * test _list_iterator_belong_to_list
 */
UT_CASE_DECLARATION(_list_iterator_belong_to_list)
void test__list_iterator_belong_to_list__null_list_container(void** state);
void test__list_iterator_belong_to_list__non_inited_list_container(void** state);
void test__list_iterator_belong_to_list__invalid_iter_container_type(void** state);
void test__list_iterator_belong_to_list__invalid_iter_iterator_type(void** state);
void test__list_iterator_belong_to_list__invalid_iter_container_pointer(void** state);
void test__list_iterator_belong_to_list__not_belong_to_list(void** state);
void test__list_iterator_belong_to_list__belong_to_list_begin(void** state);
void test__list_iterator_belong_to_list__belong_to_list_middle(void** state);
void test__list_iterator_belong_to_list__belong_to_list_end(void** state);
/*
 * test _list_same_type
 */
UT_CASE_DECLARATION(_list_same_type)
void test__list_same_type__null_first(void** state);
void test__list_same_type__null_second(void** state);
void test__list_same_type__non_created_first(void** state);
void test__list_same_type__non_created_second(void** state);
void test__list_same_type__same_c_builtin(void** state);
void test__list_same_type__same_c_builtin_dup(void** state);
void test__list_same_type__not_same_c_builtin(void** state);
void test__list_same_type__same_libcstl_builtin(void** state);
void test__list_same_type__same_libcstl_builtin_dup(void** state);
void test__list_same_type__not_same_libcstl_builtin_container(void** state);
void test__list_same_type__not_same_libcstl_builtin_elem(void** state);
void test__list_same_type__not_same_libcstl_builtin_iter(void** state);
void test__list_same_type__not_same_libcstl_builtin_string(void** state);
void test__list_same_type__not_same_c_libcstl_builtin(void** state);
void test__list_same_type__same_user_defined(void** state);
void test__list_same_type__same_user_defined_dup(void** state);
void test__list_same_type__not_same_c_user_define(void** state);
void test__list_same_type__not_same_libcstl_user_define(void** state);
void test__list_same_type__same_container(void** state);
/*
 * test _list_same_list_iterator_type
 */
UT_CASE_DECLARATION(_list_same_list_iterator_type)
void test__list_same_list_iterator_type__null_list_container(void** state);
void test__list_same_list_iterator_type__invalid_iterator_null_container(void** state);
void test__list_same_list_iterator_type__invalid_iterator_container_type(void** state);
void test__list_same_list_iterator_type__invalid_iterator_iterator_type(void** state);
void test__list_same_list_iterator_type__same_type_belong_to_list(void** state);
void test__list_same_list_iterator_type__same_type_not_belong_to_list(void** state);
void test__list_same_list_iterator_type__not_same_type(void** state);
/*
 * test _list_same_iterator_type
 */
UT_CASE_DECLARATION(_list_same_iterator_type)
void test__list_same_iterator_type__null_list_container(void** state);
void test__list_same_iterator_type__invalid_iterator_null_container(void** state);
void test__list_same_iterator_type__invalid_iterator_container_type(void** state);
void test__list_same_iterator_type__invalid_iterator_iterator_type(void** state);
void test__list_same_iterator_type__same_type_belong_to_list(void** state);
void test__list_same_iterator_type__same_type_not_belong_to_list(void** state);
void test__list_same_iterator_type__not_same_type(void** state);
void test__list_same_iterator_type__same_type_not_list_iterator(void** state);
void test__list_same_iterator_type__not_same_type_not_list_iterator(void** state);
/*
 * test _list_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_list_get_varg_value_auxiliary)
void test__list_get_varg_value_auxiliary__null_list_container(void** state);
void test__list_get_varg_value_auxiliary__null_node(void** state);
void test__list_get_varg_value_auxiliary__non_created_list_containter(void** state);
void test__list_get_varg_value_auxiliary__c_builtin(void** state);
void test__list_get_varg_value_auxiliary__cstr(void** state);
void test__list_get_varg_value_auxiliary__libcstl_builtin(void** state);
void test__list_get_varg_value_auxiliary__user_define(void** state);
/*
 * test _list_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_list_destroy_varg_value_auxiliary)
void test__list_destroy_varg_value_auxiliary__null_list_container(void** state);
void test__list_destroy_varg_value_auxiliary__non_created_list_container(void** state);
void test__list_destroy_varg_value_auxiliary__null_node(void** state);
void test__list_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _list_init_node_auxiliary
 */
UT_CASE_DECLARATION(_list_init_node_auxiliary)
void test__list_init_node_auxiliary__null_list_container(void** state);
void test__list_init_node_auxiliary__null_node(void** state);
void test__list_init_node_auxiliary__non_created_list_containter(void** state);
void test__list_init_node_auxiliary__c_builtin(void** state);
void test__list_init_node_auxiliary__cstr(void** state);
void test__list_init_node_auxiliary__libcstl_builtin(void** state);
void test__list_init_node_auxiliary__user_define(void** state);
/*
 * test _list_transfer
 */
UT_CASE_DECLARATION(_list_transfer)
void test__list_transfer__invalid_pos(void** state);
void test__list_transfer__invalid_begin(void** state);
void test__list_transfer__invalid_end(void** state);
void test__list_transfer__invalid_range_not_same_list(void** state);
void test__list_transfer__invalid_range_end_before_begin(void** state);
void test__list_transfer__pos_range_not_same_type(void** state);
void test__list_transfer__does_nothing_empty_range(void** state);
void test__list_transfer__successfully_begin_begin(void** state);
void test__list_transfer__successfully_middle_middle(void** state);
void test__list_transfer__successfully_end(void** state);
void test__list_transfer__successfully_middle_all(void** state);
void test__list_transfer__same_list_pos_belong_to_range(void** state);
void test__list_transfer__same_list_does_nothing_empty_range(void** state);
void test__list_transfer__same_list_does_nothing_pos_equa_to_begin(void** state);
void test__list_transfer__same_list_does_nothing_pos_equa_to_end(void** state);
void test__list_transfer__same_list_begin_middle(void** state);
void test__list_transfer__same_list_begin_end(void** state);
void test__list_transfer__same_list_middle_begin(void** state);
void test__list_transfer__same_list_middle_middle(void** state);
void test__list_transfer__same_list_middle_end(void** state);
void test__list_transfer__same_list_end_begin(void** state);
void test__list_transfer__same_list_end_middle(void** state);
/*
 * test _list_swap_node
 */
UT_CASE_DECLARATION(_list_swap_node)
void test__list_swap_node__null_ppt_first(void** state);
void test__list_swap_node__null_pt_first(void** state);
void test__list_swap_node__null_ppt_second(void** state);
void test__list_swap_node__null_pt_second(void** state);
void test__list_swap_node__first_followed_by_second(void** state);
void test__list_swap_node__second_followed_by_first(void** state);
void test__list_swap_node__first_distanced_by_second(void** state);
void test__list_swap_node__second_distanced_by_first(void** state);
void test__list_swap_node__same_ppt_first_ppt_second(void** state);
void test__list_swap_node__same_pt_first_pt_second(void** state);
/*
 * test _list_quick_sort
 */
UT_CASE_DECLARATION(_list_quick_sort)
void test__list_quick_sort__null_list_container(void** state);
void test__list_quick_sort__non_inited_list_container(void** state);
void test__list_quick_sort__null_pt_first(void** state);
void test__list_quick_sort__null_pt_second(void** state);
void test__list_quick_sort__invalid_range_not_belong_to_list(void** state);
void test__list_quick_sort__invalid_range(void** state);
void test__list_quick_sort__empty_less(void** state);
void test__list_quick_sort__empty_greater(void** state);
void test__list_quick_sort__1_less(void** state);
void test__list_quick_sort__1_greater(void** state);
void test__list_quick_sort__2_equal_less(void** state);
void test__list_quick_sort__2_equal_greater(void** state);
void test__list_quick_sort__2_less_less(void** state);
void test__list_quick_sort__2_less_greater(void** state);
void test__list_quick_sort__2_greater_less(void** state);
void test__list_quick_sort__2_greater_greater(void** state);
void test__list_quick_sort__random_equal_less(void** state);
void test__list_quick_sort__random_equal_greater(void** state);
void test__list_quick_sort__random_less_less(void** state);
void test__list_quick_sort__random_less_greater(void** state);
void test__list_quick_sort__random_greater_less(void** state);
void test__list_quick_sort__random_greater_greater(void** state);
void test__list_quick_sort__random_random_less(void** state);
void test__list_quick_sort__random_random_greater(void** state);
void test__list_quick_sort__random_random_dup_less(void** state);
void test__list_quick_sort__random_random_dup_greater(void** state);
void test__list_quick_sort__cstr_empty_less(void** state);
void test__list_quick_sort__cstr_empty_greater(void** state);
void test__list_quick_sort__cstr_1_less(void** state);
void test__list_quick_sort__cstr_1_greater(void** state);
void test__list_quick_sort__cstr_2_equal_less(void** state);
void test__list_quick_sort__cstr_2_equal_greater(void** state);
void test__list_quick_sort__cstr_2_less_less(void** state);
void test__list_quick_sort__cstr_2_less_greater(void** state);
void test__list_quick_sort__cstr_2_greater_less(void** state);
void test__list_quick_sort__cstr_2_greater_greater(void** state);
void test__list_quick_sort__cstr_random_equal_less(void** state);
void test__list_quick_sort__cstr_random_equal_greater(void** state);
void test__list_quick_sort__cstr_random_less_less(void** state);
void test__list_quick_sort__cstr_random_less_greater(void** state);
void test__list_quick_sort__cstr_random_greater_less(void** state);
void test__list_quick_sort__cstr_random_greater_greater(void** state);
void test__list_quick_sort__cstr_random_random_less(void** state);
void test__list_quick_sort__cstr_random_random_greater(void** state);
void test__list_quick_sort__cstr_random_random_dup_less(void** state);
void test__list_quick_sort__cstr_random_random_dup_greater(void** state);

#define UT_CSTL_LIST_AUX_CASE \
    UT_SUIT_BEGIN(cstl_list_aux, test__list_is_created__null_list_container),\
    UT_CASE(test__list_is_created__invalid_type_style),\
    UT_CASE(test__list_is_created__invalid_type_pointer),\
    UT_CASE(test__list_is_created__null_node),\
    UT_CASE(test__list_is_created__uninited_allocator),\
    UT_CASE(test__list_is_created__successfully),\
    UT_CASE_BEGIN(_list_is_inited, test__list_is_inited__null_list_container),\
    UT_CASE(test__list_is_inited__invalid_type_styple),\
    UT_CASE(test__list_is_inited__invalid_type_pointer),\
    UT_CASE(test__list_is_inited__null_node),\
    UT_CASE(test__list_is_inited__invalid_node_prev_pointer),\
    UT_CASE(test__list_is_inited__invalid_node_next_pointer),\
    UT_CASE(test__list_is_inited__init_empty),\
    UT_CASE(test__list_is_inited__init_non_empty),\
    UT_CASE_BEGIN(_list_iterator_belong_to_list, test__list_iterator_belong_to_list__null_list_container),\
    UT_CASE(test__list_iterator_belong_to_list__non_inited_list_container),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_container_type),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_iterator_type),\
    UT_CASE(test__list_iterator_belong_to_list__invalid_iter_container_pointer),\
    UT_CASE(test__list_iterator_belong_to_list__not_belong_to_list),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_begin),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_middle),\
    UT_CASE(test__list_iterator_belong_to_list__belong_to_list_end),\
    UT_CASE_BEGIN(_list_same_type, test__list_same_type__null_first),\
    UT_CASE(test__list_same_type__null_second),\
    UT_CASE(test__list_same_type__non_created_first),\
    UT_CASE(test__list_same_type__non_created_second),\
    UT_CASE(test__list_same_type__same_c_builtin),\
    UT_CASE(test__list_same_type__same_c_builtin_dup),\
    UT_CASE(test__list_same_type__not_same_c_builtin),\
    UT_CASE(test__list_same_type__same_libcstl_builtin),\
    UT_CASE(test__list_same_type__same_libcstl_builtin_dup),\
    UT_CASE(test__list_same_type__not_same_libcstl_builtin_container),\
    UT_CASE(test__list_same_type__not_same_libcstl_builtin_elem),\
    UT_CASE(test__list_same_type__not_same_libcstl_builtin_iter),\
    UT_CASE(test__list_same_type__not_same_libcstl_builtin_string),\
    UT_CASE(test__list_same_type__not_same_c_libcstl_builtin),\
    UT_CASE(test__list_same_type__same_user_defined),\
    UT_CASE(test__list_same_type__same_user_defined_dup),\
    UT_CASE(test__list_same_type__not_same_c_user_define),\
    UT_CASE(test__list_same_type__not_same_libcstl_user_define),\
    UT_CASE(test__list_same_type__same_container),\
    UT_CASE_BEGIN(_list_same_list_iterator_type, test__list_same_list_iterator_type__null_list_container),\
    UT_CASE(test__list_same_list_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__list_same_list_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__list_same_list_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__list_same_list_iterator_type__same_type_belong_to_list),\
    UT_CASE(test__list_same_list_iterator_type__same_type_not_belong_to_list),\
    UT_CASE(test__list_same_list_iterator_type__not_same_type),\
    UT_CASE_BEGIN(_list_same_iterator_type, test__list_same_iterator_type__null_list_container),\
    UT_CASE(test__list_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__list_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__list_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__list_same_iterator_type__same_type_belong_to_list),\
    UT_CASE(test__list_same_iterator_type__same_type_not_belong_to_list),\
    UT_CASE(test__list_same_iterator_type__not_same_type),\
    UT_CASE(test__list_same_iterator_type__same_type_not_list_iterator),\
    UT_CASE(test__list_same_iterator_type__not_same_type_not_list_iterator),\
    UT_CASE_BEGIN(_list_get_varg_value_auxiliary, test__list_get_varg_value_auxiliary__null_list_container),\
    UT_CASE(test__list_get_varg_value_auxiliary__null_node),\
    UT_CASE(test__list_get_varg_value_auxiliary__non_created_list_containter),\
    UT_CASE(test__list_get_varg_value_auxiliary__c_builtin),\
    UT_CASE(test__list_get_varg_value_auxiliary__cstr),\
    UT_CASE(test__list_get_varg_value_auxiliary__libcstl_builtin),\
    UT_CASE(test__list_get_varg_value_auxiliary__user_define),\
    UT_CASE_BEGIN(_list_destroy_varg_value_auxiliary, test__list_destroy_varg_value_auxiliary__null_list_container),\
    UT_CASE(test__list_destroy_varg_value_auxiliary__non_created_list_container),\
    UT_CASE(test__list_destroy_varg_value_auxiliary__null_node),\
    UT_CASE(test__list_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_list_init_node_auxiliary, test__list_init_node_auxiliary__null_list_container),\
    UT_CASE(test__list_init_node_auxiliary__null_node),\
    UT_CASE(test__list_init_node_auxiliary__non_created_list_containter),\
    UT_CASE(test__list_init_node_auxiliary__c_builtin),\
    UT_CASE(test__list_init_node_auxiliary__cstr),\
    UT_CASE(test__list_init_node_auxiliary__libcstl_builtin),\
    UT_CASE(test__list_init_node_auxiliary__user_define),\
    UT_CASE_BEGIN(_list_transfer, test__list_transfer__invalid_pos),\
    UT_CASE(test__list_transfer__invalid_begin),\
    UT_CASE(test__list_transfer__invalid_end),\
    UT_CASE(test__list_transfer__invalid_range_not_same_list),\
    UT_CASE(test__list_transfer__invalid_range_end_before_begin),\
    UT_CASE(test__list_transfer__pos_range_not_same_type),\
    UT_CASE(test__list_transfer__does_nothing_empty_range),\
    UT_CASE(test__list_transfer__successfully_begin_begin),\
    UT_CASE(test__list_transfer__successfully_middle_middle),\
    UT_CASE(test__list_transfer__successfully_end),\
    UT_CASE(test__list_transfer__successfully_middle_all),\
    UT_CASE(test__list_transfer__same_list_pos_belong_to_range),\
    UT_CASE(test__list_transfer__same_list_does_nothing_empty_range),\
    UT_CASE(test__list_transfer__same_list_does_nothing_pos_equa_to_begin),\
    UT_CASE(test__list_transfer__same_list_does_nothing_pos_equa_to_end),\
    UT_CASE(test__list_transfer__same_list_begin_middle),\
    UT_CASE(test__list_transfer__same_list_begin_end),\
    UT_CASE(test__list_transfer__same_list_middle_begin),\
    UT_CASE(test__list_transfer__same_list_middle_middle),\
    UT_CASE(test__list_transfer__same_list_middle_end),\
    UT_CASE(test__list_transfer__same_list_end_begin),\
    UT_CASE(test__list_transfer__same_list_end_middle),\
    UT_CASE_BEGIN(_list_swap_node, test__list_swap_node__null_ppt_first),\
    UT_CASE(test__list_swap_node__null_pt_first),\
    UT_CASE(test__list_swap_node__null_ppt_second),\
    UT_CASE(test__list_swap_node__null_pt_second),\
    UT_CASE(test__list_swap_node__first_followed_by_second),\
    UT_CASE(test__list_swap_node__second_followed_by_first),\
    UT_CASE(test__list_swap_node__first_distanced_by_second),\
    UT_CASE(test__list_swap_node__second_distanced_by_first),\
    UT_CASE(test__list_swap_node__same_ppt_first_ppt_second),\
    UT_CASE(test__list_swap_node__same_pt_first_pt_second),\
    UT_CASE_BEGIN(_list_quick_sort, test__list_quick_sort__null_list_container),\
    UT_CASE(test__list_quick_sort__non_inited_list_container),\
    UT_CASE(test__list_quick_sort__null_pt_first),\
    UT_CASE(test__list_quick_sort__null_pt_second),\
    UT_CASE(test__list_quick_sort__invalid_range_not_belong_to_list),\
    UT_CASE(test__list_quick_sort__invalid_range),\
    UT_CASE(test__list_quick_sort__empty_less),\
    UT_CASE(test__list_quick_sort__empty_greater),\
    UT_CASE(test__list_quick_sort__1_less),\
    UT_CASE(test__list_quick_sort__1_greater),\
    UT_CASE(test__list_quick_sort__2_equal_less),\
    UT_CASE(test__list_quick_sort__2_equal_greater),\
    UT_CASE(test__list_quick_sort__2_less_less),\
    UT_CASE(test__list_quick_sort__2_less_greater),\
    UT_CASE(test__list_quick_sort__2_greater_less),\
    UT_CASE(test__list_quick_sort__2_greater_greater),\
    UT_CASE(test__list_quick_sort__random_equal_less),\
    UT_CASE(test__list_quick_sort__random_equal_greater),\
    UT_CASE(test__list_quick_sort__random_less_less),\
    UT_CASE(test__list_quick_sort__random_less_greater),\
    UT_CASE(test__list_quick_sort__random_greater_less),\
    UT_CASE(test__list_quick_sort__random_greater_greater),\
    UT_CASE(test__list_quick_sort__random_random_less),\
    UT_CASE(test__list_quick_sort__random_random_greater),\
    UT_CASE(test__list_quick_sort__random_random_dup_less),\
    UT_CASE(test__list_quick_sort__random_random_dup_greater),\
    UT_CASE(test__list_quick_sort__cstr_empty_less),\
    UT_CASE(test__list_quick_sort__cstr_empty_greater),\
    UT_CASE(test__list_quick_sort__cstr_1_less),\
    UT_CASE(test__list_quick_sort__cstr_1_greater),\
    UT_CASE(test__list_quick_sort__cstr_2_equal_less),\
    UT_CASE(test__list_quick_sort__cstr_2_equal_greater),\
    UT_CASE(test__list_quick_sort__cstr_2_less_less),\
    UT_CASE(test__list_quick_sort__cstr_2_less_greater),\
    UT_CASE(test__list_quick_sort__cstr_2_greater_less),\
    UT_CASE(test__list_quick_sort__cstr_2_greater_greater),\
    UT_CASE(test__list_quick_sort__cstr_random_equal_less),\
    UT_CASE(test__list_quick_sort__cstr_random_equal_greater),\
    UT_CASE(test__list_quick_sort__cstr_random_less_less),\
    UT_CASE(test__list_quick_sort__cstr_random_less_greater),\
    UT_CASE(test__list_quick_sort__cstr_random_greater_less),\
    UT_CASE(test__list_quick_sort__cstr_random_greater_greater),\
    UT_CASE(test__list_quick_sort__cstr_random_random_less),\
    UT_CASE(test__list_quick_sort__cstr_random_random_greater),\
    UT_CASE(test__list_quick_sort__cstr_random_random_dup_less),\
    UT_CASE(test__list_quick_sort__cstr_random_random_dup_greater)

#endif /* _UT_CSTL_LIST_AUX_H_ */

