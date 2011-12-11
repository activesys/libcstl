#ifndef _UT_CSTL_DEQUE_AUX_H_
#define _UT_CSTL_DEQUE_AUX_H_

UT_SUIT_DECLARATION(cstl_deque_aux)

/*
 * test _deque_is_created
 */
UT_CASE_DECLARATION(_deque_is_created)
void test__deque_is_created__null_deque_container(void** state);
void test__deque_is_created__non_created_invalid_start(void** state);
void test__deque_is_created__non_created_invalid_finish(void** state);
void test__deque_is_created__non_created_invalid_type_style(void** state);
void test__deque_is_created__non_created_non_init_allocator(void** state);
void test__deque_is_created__non_created_invalid_map(void** state);
void test__deque_is_created__non_created_invalid_mapsize(void** state);
void test__deque_is_created__created(void** state);
/*
 * test _deque_is_inited
 */
UT_CASE_DECLARATION(_deque_is_inited)
void test__deque_is_inited__null_deque_container(void** state);
void test__deque_is_inited__invalid_type_style(void** state);
void test__deque_is_inited__invalid_type_pointer(void** state);
void test__deque_is_inited__invalid_map(void** state);
void test__deque_is_inited__invalid_mapsize(void** state);
void test__deque_is_inited__invalid_mapsize_not_grow_count_multiple(void** state);
void test__deque_is_inited__invalid_start(void** state);
void test__deque_is_inited__invalid_finish(void** state);
void test__deque_is_inited__init(void** state);
void test__deque_is_inited__init_n(void** state);
void test__deque_is_inited__init_elem(void** state);
/*
 * test _deque_iterator_belong_to_deque
 */
UT_CASE_DECLARATION(_deque_iterator_belong_to_deque)
void test__deque_iterator_belong_to_deque__null_container_pointer(void** state);
void test__deque_iterator_belong_to_deque__non_inited_deque_container(void** state);
void test__deque_iterator_belong_to_deque__invalid_iterator_container_type(void** state);
void test__deque_iterator_belong_to_deque__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_belong_to_deque__invalid_iterator_different_container(void** state);
void test__deque_iterator_belong_to_deque__invalid_map(void** state);
void test__deque_iterator_belong_to_deque__invalid_first_pos(void** state);
void test__deque_iterator_belong_to_deque__invalid_afterlast_pos(void** state);
void test__deque_iterator_belong_to_deque__less_than_begin(void** state);
void test__deque_iterator_belong_to_deque__within_deque(void** state);
void test__deque_iterator_belong_to_deque__end_iterator(void** state);
void test__deque_iterator_belong_to_deque__greater_than_end(void** state);
void test__deque_iterator_belong_to_deque__border(void** state);
/*
 * test _deque_same_type
 */
UT_CASE_DECLARATION(_deque_same_type)
void test__deque_same_type__null_first(void** state);
void test__deque_same_type__null_second(void** state);
void test__deque_same_type__non_created_first(void** state);
void test__deque_same_type__non_created_second(void** state);
void test__deque_same_type__same_c_builtin(void** state);
void test__deque_same_type__same_c_builtin_dup(void** state);
void test__deque_same_type__not_same_c_builtin(void** state);
void test__deque_same_type__same_libcstl_builtin(void** state);
void test__deque_same_type__same_libcstl_builtin_dup(void** state);
void test__deque_same_type__not_same_libcstl_builtin_container(void** state);
void test__deque_same_type__not_same_libcstl_builtin_elem(void** state);
void test__deque_same_type__not_same_libcstl_builtin_iter(void** state);
void test__deque_same_type__not_same_libcstl_builtin_string(void** state);
void test__deque_same_type__not_same_c_libcstl_builtin(void** state);
void test__deque_same_type__same_user_defined(void** state);
void test__deque_same_type__same_user_defined_dup(void** state);
void test__deque_same_type__not_same_c_user_define(void** state);
void test__deque_same_type__not_same_libcstl_user_define(void** state);
void test__deque_same_type__same_container(void** state);
/*
 * test _deque_same_deque_iterator_type
 */
UT_CASE_DECLARATION(_deque_same_deque_iterator_type)
void test__deque_same_deque_iterator_type__null_deque_container(void** state);
void test__deque_same_deque_iterator_type__invalid_iterator_null_container(void** state);
void test__deque_same_deque_iterator_type__invalid_iterator_container_type(void** state);
void test__deque_same_deque_iterator_type__invalid_iterator_iterator_type(void** state);
void test__deque_same_deque_iterator_type__same_type_belong_to_deque(void** state);
void test__deque_same_deque_iterator_type__same_type_not_belong_to_deque(void** state);
void test__deque_same_deque_iterator_type__not_same_type(void** state);
/*
 * test _deque_same_iterator_type
 */
UT_CASE_DECLARATION(_deque_same_iterator_type)
void test__deque_same_iterator_type__null_deque_container(void** state);
void test__deque_same_iterator_type__invalid_iterator_null_container(void** state);
void test__deque_same_iterator_type__invalid_iterator_container_type(void** state);
void test__deque_same_iterator_type__invalid_iterator_iterator_type(void** state);
void test__deque_same_iterator_type__same_type_belong_to_deque(void** state);
void test__deque_same_iterator_type__same_type_not_belong_to_deque(void** state);
void test__deque_same_iterator_type__not_same_type(void** state);
void test__deque_same_iterator_type__same_type_not_deque_iterator(void** state);
void test__deque_same_iterator_type__not_same_type_not_deque_iterator(void** state);
/*
 * test _deque_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_deque_get_varg_value_auxiliary)
void test__deque_get_varg_value_auxiliary__null_deque_container(void** state);
void test__deque_get_varg_value_auxiliary__null_node(void** state);
void test__deque_get_varg_value_auxiliary__non_created_deque_containter(void** state);
void test__deque_get_varg_value_auxiliary__c_builtin(void** state);
void test__deque_get_varg_value_auxiliary__cstr(void** state);
void test__deque_get_varg_value_auxiliary__libcstl_builtin(void** state);
void test__deque_get_varg_value_auxiliary__user_define(void** state);
/*
 * test _deque_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_deque_destroy_varg_value_auxiliary)
void test__deque_destroy_varg_value_auxiliary__null_deque_container(void** state);
void test__deque_destroy_varg_value_auxiliary__null_varg(void** state);
void test__deque_destroy_varg_value_auxiliary__non_created(void** state);
void test__deque_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _deque_init_elem_range_auxiliary
 */
UT_CASE_DECLARATION(_deque_init_elem_range_auxiliary)
void test__deque_init_elem_range_auxiliary__null_deque_containter(void** state);
void test__deque_init_elem_range_auxiliary__invalid_range_begin(void** state);
void test__deque_init_elem_range_auxiliary__invalid_range_end(void** state);
void test__deque_init_elem_range_auxiliary__invalid_range(void** state);
void test__deque_init_elem_range_auxiliary__non_created(void** state);
void test__deque_init_elem_range_auxiliary__successfully_empty_range(void** state);
void test__deque_init_elem_range_auxiliary__successfully_int(void** state);
void test__deque_init_elem_range_auxiliary__successfully_cstr(void** state);
void test__deque_init_elem_range_auxiliary__successfully_iterator(void** state);
void test__deque_init_elem_range_auxiliary__successfully_container(void** state);
/*
 * test _deque_iterator_get_pointer_auxiliary
 */
UT_CASE_DECLARATION(_deque_iterator_get_pointer_auxiliary)
void test__deque_iterator_get_pointer_auxiliary__invalid_iterator(void** state);
void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_type(void** state);
void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_iterator_type(void** state);
void test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_pointer(void** state);
void test__deque_iterator_get_pointer_auxiliary__deque_end(void** state);
void test__deque_iterator_get_pointer_auxiliary__successfully_not_border(void** state);
void test__deque_iterator_get_pointer_auxiliary__successfully_border(void** state);
void test__deque_iterator_get_pointer_auxiliary__successfully_cstr_not_border(void** state);
void test__deque_iterator_get_pointer_auxiliary__successfully_cstr_border(void** state);
/*
 * test _deque_expand_at_end
 */
UT_CASE_DECLARATION(_deque_expand_at_end)
void test__deque_expand_at_end__null_deque_container(void** state);
void test__deque_expand_at_end__non_inited_deque_container(void** state);
void test__deque_expand_at_end__invalid_iterator(void** state);
void test__deque_expand_at_end__expand_0(void** state);
void test__deque_expand_at_end__expand_less_than_chunk(void** state);
void test__deque_expand_at_end__expand_less_than_chunk_pos(void** state);
void test__deque_expand_at_end__expand_one_chunk(void** state);
void test__deque_expand_at_end__expand_one_chunk_pos(void** state);
void test__deque_expand_at_end__expand_more_than_one_chunk(void** state);
void test__deque_expand_at_end__expand_more_than_one_chunk_pos(void** state);
void test__deque_expand_at_end__expand_remain_map_end(void** state);
void test__deque_expand_at_end__expand_remain_map_pos_end(void** state);
void test__deque_expand_at_end__expand_move_map(void** state);
void test__deque_expand_at_end__expand_move_map_pos(void** state);
void test__deque_expand_at_end__expand_full_map(void** state);
void test__deque_expand_at_end__expand_full_map_pos(void** state);
void test__deque_expand_at_end__expand_map(void** state);
void test__deque_expand_at_end__expand_map_pos(void** state);
/*
 * test _deque_expand_at_begin
 */
UT_CASE_DECLARATION(_deque_expand_at_begin)
void test__deque_expand_at_begin__null_deque_container(void** state);
void test__deque_expand_at_begin__non_inited_deque_container(void** state);
void test__deque_expand_at_begin__invalid_iterator(void** state);
void test__deque_expand_at_begin__expand_0(void** state);
void test__deque_expand_at_begin__expand_less_than_chunk(void** state);
void test__deque_expand_at_begin__expand_less_than_chunk_pos(void** state);
void test__deque_expand_at_begin__expand_one_chunk(void** state);
void test__deque_expand_at_begin__expand_one_chunk_pos(void** state);
void test__deque_expand_at_begin__expand_more_than_one_chunk(void** state);
void test__deque_expand_at_begin__expand_more_than_one_chunk_pos(void** state);
void test__deque_expand_at_begin__expand_remain_map_begin(void** state);
void test__deque_expand_at_begin__expand_remain_map_pos_begin(void** state);
void test__deque_expand_at_begin__expand_move_map(void** state);
void test__deque_expand_at_begin__expand_move_map_pos(void** state);
void test__deque_expand_at_begin__expand_full_map(void** state);
void test__deque_expand_at_begin__expand_full_map_pos(void** state);
void test__deque_expand_at_begin__expand_map(void** state);
void test__deque_expand_at_begin__expand_map_pos(void** state);
/*
 * test _deque_shrink_at_end
 */
UT_CASE_DECLARATION(_deque_shrink_at_end)
void test__deque_shrink_at_end__null_deque_container(void** state);
void test__deque_shrink_at_end__non_inited_deque_container(void** state);
void test__deque_shrink_at_end__empty_shrink_0(void** state);
void test__deque_shrink_at_end__empty_shrink_6(void** state);
void test__deque_shrink_at_end__begin_border_shrink_0(void** state);
void test__deque_shrink_at_end__begin_border_shrink_less_size(void** state);
void test__deque_shrink_at_end__begin_border_shrink_equal_to_size(void** state);
void test__deque_shrink_at_end__begin_border_shrink_greater_than_size(void** state);
void test__deque_shrink_at_end__end_border_shrink_0(void** state);
void test__deque_shrink_at_end__end_border_shrink_less_size(void** state);
void test__deque_shrink_at_end__end_border_shrink_equal_to_size(void** state);
void test__deque_shrink_at_end__end_border_shrink_greater_than_size(void** state);
/*
 * test _deque_shrink_at_begin
 */
UT_CASE_DECLARATION(_deque_shrink_at_begin)
void test__deque_shrink_at_begin__null_deque_container(void** state);
void test__deque_shrink_at_begin__non_inited_deque_container(void** state);
void test__deque_shrink_at_begin__empty_shrink_0(void** state);
void test__deque_shrink_at_begin__empty_shrink_6(void** state);
void test__deque_shrink_at_begin__begin_border_shrink_0(void** state);
void test__deque_shrink_at_begin__begin_border_shrink_less_size(void** state);
void test__deque_shrink_at_begin__begin_border_shrink_equal_to_size(void** state);
void test__deque_shrink_at_begin__begin_border_shrink_greater_than_size(void** state);
void test__deque_shrink_at_begin__end_border_shrink_0(void** state);
void test__deque_shrink_at_begin__end_border_shrink_less_size(void** state);
void test__deque_shrink_at_begin__end_border_shrink_equal_to_size(void** state);
void test__deque_shrink_at_begin__end_border_shrink_greater_than_size(void** state);
/*
 * test _deque_move_elem_to_end
 */
UT_CASE_DECLARATION(_deque_move_elem_to_end)
void test__deque_move_elem_to_end__null_deque_container(void** state);
void test__deque_move_elem_to_end__non_inited_deque_container(void** state);
void test__deque_move_elem_to_end__invalid_range(void** state);
void test__deque_move_elem_to_end__invalid_range_after_moving(void** state);
void test__deque_move_elem_to_end__empty(void** state);
void test__deque_move_elem_to_end__0_step(void** state);
void test__deque_move_elem_to_end__begin_to_end(void** state);
void test__deque_move_elem_to_end__begin_to_middle(void** state);
void test__deque_move_elem_to_end__middle_to_end(void** state);
void test__deque_move_elem_to_end__middle_to_middle(void** state);
/*
 * test _deque_move_elem_to_begin
 */
UT_CASE_DECLARATION(_deque_move_elem_to_begin)
void test__deque_move_elem_to_begin__null_deque_container(void** state);
void test__deque_move_elem_to_begin__non_inited_deque_container(void** state);
void test__deque_move_elem_to_begin__invalid_range(void** state);
void test__deque_move_elem_to_begin__invalid_range_after_moving(void** state);
void test__deque_move_elem_to_begin__empty(void** state);
void test__deque_move_elem_to_begin__0_step(void** state);
void test__deque_move_elem_to_begin__end_to_begin(void** state);
void test__deque_move_elem_to_begin__end_to_middle(void** state);
void test__deque_move_elem_to_begin__middle_to_begin(void** state);
void test__deque_move_elem_to_begin__middle_to_middle(void** state);

#define UT_CSTL_DEQUE_AUX_CASE\
    UT_SUIT_BEGIN(cstl_deque_aux, test__deque_is_created__null_deque_container),\
    UT_CASE(test__deque_is_created__non_created_invalid_start),\
    UT_CASE(test__deque_is_created__non_created_invalid_finish),\
    UT_CASE(test__deque_is_created__non_created_invalid_type_style),\
    UT_CASE(test__deque_is_created__non_created_non_init_allocator),\
    UT_CASE(test__deque_is_created__non_created_invalid_map),\
    UT_CASE(test__deque_is_created__non_created_invalid_mapsize),\
    UT_CASE(test__deque_is_created__created),\
    UT_CASE_BEGIN(_deque_is_inited, test__deque_is_inited__null_deque_container),\
    UT_CASE(test__deque_is_inited__invalid_type_style),\
    UT_CASE(test__deque_is_inited__invalid_type_pointer),\
    UT_CASE(test__deque_is_inited__invalid_map),\
    UT_CASE(test__deque_is_inited__invalid_mapsize),\
    UT_CASE(test__deque_is_inited__invalid_mapsize_not_grow_count_multiple),\
    UT_CASE(test__deque_is_inited__invalid_start),\
    UT_CASE(test__deque_is_inited__invalid_finish),\
    UT_CASE(test__deque_is_inited__init),\
    UT_CASE(test__deque_is_inited__init_n),\
    UT_CASE(test__deque_is_inited__init_elem),\
    UT_CASE_BEGIN(_deque_iterator_belong_to_deque, test__deque_iterator_belong_to_deque__null_container_pointer),\
    UT_CASE(test__deque_iterator_belong_to_deque__non_inited_deque_container),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_iterator_different_container),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_map),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_first_pos),\
    UT_CASE(test__deque_iterator_belong_to_deque__invalid_afterlast_pos),\
    UT_CASE(test__deque_iterator_belong_to_deque__less_than_begin),\
    UT_CASE(test__deque_iterator_belong_to_deque__within_deque),\
    UT_CASE(test__deque_iterator_belong_to_deque__end_iterator),\
    UT_CASE(test__deque_iterator_belong_to_deque__greater_than_end),\
    UT_CASE(test__deque_iterator_belong_to_deque__border),\
    UT_CASE_BEGIN(_deque_same_type, test__deque_same_type__null_first),\
    UT_CASE(test__deque_same_type__null_second),\
    UT_CASE(test__deque_same_type__non_created_first),\
    UT_CASE(test__deque_same_type__non_created_second),\
    UT_CASE(test__deque_same_type__same_c_builtin),\
    UT_CASE(test__deque_same_type__same_c_builtin_dup),\
    UT_CASE(test__deque_same_type__not_same_c_builtin),\
    UT_CASE(test__deque_same_type__same_libcstl_builtin),\
    UT_CASE(test__deque_same_type__same_libcstl_builtin_dup),\
    UT_CASE(test__deque_same_type__not_same_libcstl_builtin_container),\
    UT_CASE(test__deque_same_type__not_same_libcstl_builtin_elem),\
    UT_CASE(test__deque_same_type__not_same_libcstl_builtin_iter),\
    UT_CASE(test__deque_same_type__not_same_libcstl_builtin_string),\
    UT_CASE(test__deque_same_type__not_same_c_libcstl_builtin),\
    UT_CASE(test__deque_same_type__same_user_defined),\
    UT_CASE(test__deque_same_type__same_user_defined_dup),\
    UT_CASE(test__deque_same_type__not_same_c_user_define),\
    UT_CASE(test__deque_same_type__not_same_libcstl_user_define),\
    UT_CASE(test__deque_same_type__same_container),\
    UT_CASE_BEGIN(_deque_same_deque_iterator_type, test__deque_same_deque_iterator_type__null_deque_container),\
    UT_CASE(test__deque_same_deque_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__deque_same_deque_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__deque_same_deque_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_same_deque_iterator_type__same_type_belong_to_deque),\
    UT_CASE(test__deque_same_deque_iterator_type__same_type_not_belong_to_deque),\
    UT_CASE(test__deque_same_deque_iterator_type__not_same_type),\
    UT_CASE_BEGIN(_deque_same_iterator_type, test__deque_same_iterator_type__null_deque_container),\
    UT_CASE(test__deque_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__deque_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__deque_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_same_iterator_type__same_type_belong_to_deque),\
    UT_CASE(test__deque_same_iterator_type__same_type_not_belong_to_deque),\
    UT_CASE(test__deque_same_iterator_type__not_same_type),\
    UT_CASE(test__deque_same_iterator_type__same_type_not_deque_iterator),\
    UT_CASE(test__deque_same_iterator_type__not_same_type_not_deque_iterator),\
    UT_CASE_BEGIN(_deque_get_varg_value_auxiliary, test__deque_get_varg_value_auxiliary__null_deque_container),\
    UT_CASE(test__deque_get_varg_value_auxiliary__null_node),\
    UT_CASE(test__deque_get_varg_value_auxiliary__non_created_deque_containter),\
    UT_CASE(test__deque_get_varg_value_auxiliary__c_builtin),\
    UT_CASE(test__deque_get_varg_value_auxiliary__cstr),\
    UT_CASE(test__deque_get_varg_value_auxiliary__libcstl_builtin),\
    UT_CASE(test__deque_get_varg_value_auxiliary__user_define),\
    UT_CASE_BEGIN(_deque_destroy_varg_value_auxiliary, test__deque_destroy_varg_value_auxiliary__null_deque_container),\
    UT_CASE(test__deque_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__deque_destroy_varg_value_auxiliary__non_created),\
    UT_CASE(test__deque_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_deque_init_elem_range_auxiliary, test__deque_init_elem_range_auxiliary__null_deque_containter),\
    UT_CASE(test__deque_init_elem_range_auxiliary__invalid_range_begin),\
    UT_CASE(test__deque_init_elem_range_auxiliary__invalid_range_end),\
    UT_CASE(test__deque_init_elem_range_auxiliary__invalid_range),\
    UT_CASE(test__deque_init_elem_range_auxiliary__non_created),\
    UT_CASE(test__deque_init_elem_range_auxiliary__successfully_empty_range),\
    UT_CASE(test__deque_init_elem_range_auxiliary__successfully_int),\
    UT_CASE(test__deque_init_elem_range_auxiliary__successfully_cstr),\
    UT_CASE(test__deque_init_elem_range_auxiliary__successfully_iterator),\
    UT_CASE(test__deque_init_elem_range_auxiliary__successfully_container),\
    UT_CASE_BEGIN(_deque_iterator_get_pointer_auxiliary, test__deque_iterator_get_pointer_auxiliary__invalid_iterator),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_type),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__invalid_iterator_iterator_type),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__invalid_iterator_container_pointer),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__deque_end),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__successfully_not_border),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__successfully_border),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__successfully_cstr_not_border),\
    UT_CASE(test__deque_iterator_get_pointer_auxiliary__successfully_cstr_border),\
    UT_CASE_BEGIN(_deque_expand_at_end, test__deque_expand_at_end__null_deque_container),\
    UT_CASE(test__deque_expand_at_end__non_inited_deque_container),\
    UT_CASE(test__deque_expand_at_end__invalid_iterator),\
    UT_CASE(test__deque_expand_at_end__expand_0),\
    UT_CASE(test__deque_expand_at_end__expand_less_than_chunk),\
    UT_CASE(test__deque_expand_at_end__expand_less_than_chunk_pos),\
    UT_CASE(test__deque_expand_at_end__expand_one_chunk),\
    UT_CASE(test__deque_expand_at_end__expand_one_chunk_pos),\
    UT_CASE(test__deque_expand_at_end__expand_more_than_one_chunk),\
    UT_CASE(test__deque_expand_at_end__expand_more_than_one_chunk_pos),\
    UT_CASE(test__deque_expand_at_end__expand_remain_map_end),\
    UT_CASE(test__deque_expand_at_end__expand_remain_map_pos_end),\
    UT_CASE(test__deque_expand_at_end__expand_move_map),\
    UT_CASE(test__deque_expand_at_end__expand_move_map_pos),\
    UT_CASE(test__deque_expand_at_end__expand_full_map),\
    UT_CASE(test__deque_expand_at_end__expand_full_map_pos),\
    UT_CASE(test__deque_expand_at_end__expand_map),\
    UT_CASE(test__deque_expand_at_end__expand_map_pos),\
    UT_CASE_BEGIN(_deque_expand_at_begin, test__deque_expand_at_begin__null_deque_container),\
    UT_CASE(test__deque_expand_at_begin__non_inited_deque_container),\
    UT_CASE(test__deque_expand_at_begin__invalid_iterator),\
    UT_CASE(test__deque_expand_at_begin__expand_0),\
    UT_CASE(test__deque_expand_at_begin__expand_less_than_chunk),\
    UT_CASE(test__deque_expand_at_begin__expand_less_than_chunk_pos),\
    UT_CASE(test__deque_expand_at_begin__expand_one_chunk),\
    UT_CASE(test__deque_expand_at_begin__expand_one_chunk_pos),\
    UT_CASE(test__deque_expand_at_begin__expand_more_than_one_chunk),\
    UT_CASE(test__deque_expand_at_begin__expand_more_than_one_chunk_pos),\
    UT_CASE(test__deque_expand_at_begin__expand_remain_map_begin),\
    UT_CASE(test__deque_expand_at_begin__expand_remain_map_pos_begin),\
    UT_CASE(test__deque_expand_at_begin__expand_move_map),\
    UT_CASE(test__deque_expand_at_begin__expand_move_map_pos),\
    UT_CASE(test__deque_expand_at_begin__expand_full_map),\
    UT_CASE(test__deque_expand_at_begin__expand_full_map_pos),\
    UT_CASE(test__deque_expand_at_begin__expand_map),\
    UT_CASE(test__deque_expand_at_begin__expand_map_pos),\
    UT_CASE_BEGIN(_deque_shrink_at_end, test__deque_shrink_at_end__null_deque_container),\
    UT_CASE(test__deque_shrink_at_end__non_inited_deque_container),\
    UT_CASE(test__deque_shrink_at_end__empty_shrink_0),\
    UT_CASE(test__deque_shrink_at_end__empty_shrink_6),\
    UT_CASE(test__deque_shrink_at_end__begin_border_shrink_0),\
    UT_CASE(test__deque_shrink_at_end__begin_border_shrink_less_size),\
    UT_CASE(test__deque_shrink_at_end__begin_border_shrink_equal_to_size),\
    UT_CASE(test__deque_shrink_at_end__begin_border_shrink_greater_than_size),\
    UT_CASE(test__deque_shrink_at_end__end_border_shrink_0),\
    UT_CASE(test__deque_shrink_at_end__end_border_shrink_less_size),\
    UT_CASE(test__deque_shrink_at_end__end_border_shrink_equal_to_size),\
    UT_CASE(test__deque_shrink_at_end__end_border_shrink_greater_than_size),\
    UT_CASE_BEGIN(_deque_shrink_at_begin, test__deque_shrink_at_begin__null_deque_container),\
    UT_CASE(test__deque_shrink_at_begin__non_inited_deque_container),\
    UT_CASE(test__deque_shrink_at_begin__empty_shrink_0),\
    UT_CASE(test__deque_shrink_at_begin__empty_shrink_6),\
    UT_CASE(test__deque_shrink_at_begin__begin_border_shrink_0),\
    UT_CASE(test__deque_shrink_at_begin__begin_border_shrink_less_size),\
    UT_CASE(test__deque_shrink_at_begin__begin_border_shrink_equal_to_size),\
    UT_CASE(test__deque_shrink_at_begin__begin_border_shrink_greater_than_size),\
    UT_CASE(test__deque_shrink_at_begin__end_border_shrink_0),\
    UT_CASE(test__deque_shrink_at_begin__end_border_shrink_less_size),\
    UT_CASE(test__deque_shrink_at_begin__end_border_shrink_equal_to_size),\
    UT_CASE(test__deque_shrink_at_begin__end_border_shrink_greater_than_size),\
    UT_CASE_BEGIN(_deque_move_elem_to_end, test__deque_move_elem_to_end__null_deque_container),\
    UT_CASE(test__deque_move_elem_to_end__non_inited_deque_container),\
    UT_CASE(test__deque_move_elem_to_end__invalid_range),\
    UT_CASE(test__deque_move_elem_to_end__invalid_range_after_moving),\
    UT_CASE(test__deque_move_elem_to_end__empty),\
    UT_CASE(test__deque_move_elem_to_end__0_step),\
    UT_CASE(test__deque_move_elem_to_end__begin_to_end),\
    UT_CASE(test__deque_move_elem_to_end__begin_to_middle),\
    UT_CASE(test__deque_move_elem_to_end__middle_to_end),\
    UT_CASE(test__deque_move_elem_to_end__middle_to_middle),\
    UT_CASE_BEGIN(_deque_move_elem_to_begin, test__deque_move_elem_to_begin__null_deque_container),\
    UT_CASE(test__deque_move_elem_to_begin__non_inited_deque_container),\
    UT_CASE(test__deque_move_elem_to_begin__invalid_range),\
    UT_CASE(test__deque_move_elem_to_begin__invalid_range_after_moving),\
    UT_CASE(test__deque_move_elem_to_begin__empty),\
    UT_CASE(test__deque_move_elem_to_begin__0_step),\
    UT_CASE(test__deque_move_elem_to_begin__end_to_begin),\
    UT_CASE(test__deque_move_elem_to_begin__end_to_middle),\
    UT_CASE(test__deque_move_elem_to_begin__middle_to_begin),\
    UT_CASE(test__deque_move_elem_to_begin__middle_to_middle)

#endif /* _UT_CSTL_DEQUE_AUX_H_ */

