#ifndef _UT_CSTL_SLIST_AUX_H_
#define _UT_CSTL_SLIST_AUX_H_

UT_SUIT_DECLARATION(cstl_slist_aux)

/*
 * test _slist_is_created
 */
UT_CASE_DECLARATION(_slist_is_created)
void test__slist_is_created__null_slist_container(void** state);
void test__slist_is_created__invalid_type_style(void** state);
void test__slist_is_created__invalid_type_pointer(void** state);
void test__slist_is_created__null_node(void** state);
void test__slist_is_created__uninited_allocator(void** state);
void test__slist_is_created__successfully(void** state);
/*
 * test _slist_is_inited
 */
UT_CASE_DECLARATION(_slist_is_inited)
void test__slist_is_inited__null_slist_container(void** state);
void test__slist_is_inited__invalid_type_styple(void** state);
void test__slist_is_inited__invalid_type_pointer(void** state);
void test__slist_is_inited__init_empty(void** state);
void test__slist_is_inited__init_non_empty(void** state);
/*
 * test _slist_iterator_belong_to_slist
 */
UT_CASE_DECLARATION(_slist_iterator_belong_to_slist)
void test__slist_iterator_belong_to_slist__null_slist_container(void** state);
void test__slist_iterator_belong_to_slist__non_inited_slist_container(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_container_type(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_iterator_type(void** state);
void test__slist_iterator_belong_to_slist__invalid_iter_container_pointer(void** state);
void test__slist_iterator_belong_to_slist__not_belong_to_slist(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_begin(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_middle(void** state);
void test__slist_iterator_belong_to_slist__belong_to_slist_end(void** state);
/*
 * test _slist_same_type
 */
UT_CASE_DECLARATION(_slist_same_type)
void test__slist_same_type__null_first(void** state);
void test__slist_same_type__null_second(void** state);
void test__slist_same_type__non_created_first(void** state);
void test__slist_same_type__non_created_second(void** state);
void test__slist_same_type__same_c_builtin(void** state);
void test__slist_same_type__same_c_builtin_dup(void** state);
void test__slist_same_type__not_same_c_builtin(void** state);
void test__slist_same_type__same_libcstl_builtin(void** state);
void test__slist_same_type__same_libcstl_builtin_dup(void** state);
void test__slist_same_type__not_same_libcstl_builtin_container(void** state);
void test__slist_same_type__not_same_libcstl_builtin_elem(void** state);
void test__slist_same_type__not_same_libcstl_builtin_iter(void** state);
void test__slist_same_type__not_same_libcstl_builtin_string(void** state);
void test__slist_same_type__not_same_c_libcstl_builtin(void** state);
void test__slist_same_type__same_user_defined(void** state);
void test__slist_same_type__same_user_defined_dup(void** state);
void test__slist_same_type__not_same_c_user_define(void** state);
void test__slist_same_type__not_same_libcstl_user_define(void** state);
void test__slist_same_type__same_container(void** state);
/*
 * test _slist_same_slist_iterator_type
 */
UT_CASE_DECLARATION(_slist_same_slist_iterator_type)
void test__slist_same_slist_iterator_type__null_slist_container(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_null_container(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_container_type(void** state);
void test__slist_same_slist_iterator_type__invalid_iterator_iterator_type(void** state);
void test__slist_same_slist_iterator_type__same_type_belong_to_slist(void** state);
void test__slist_same_slist_iterator_type__same_type_not_belong_to_slist(void** state);
void test__slist_same_slist_iterator_type__not_same_type(void** state);
/*
 * test _slist_same_iterator_type
 */
UT_CASE_DECLARATION(_slist_same_iterator_type)
void test__slist_same_iterator_type__null_slist_container(void** state);
void test__slist_same_iterator_type__invalid_iterator_null_container(void** state);
void test__slist_same_iterator_type__invalid_iterator_container_type(void** state);
void test__slist_same_iterator_type__invalid_iterator_iterator_type(void** state);
void test__slist_same_iterator_type__same_type_belong_to_slist(void** state);
void test__slist_same_iterator_type__same_type_not_belong_to_slist(void** state);
void test__slist_same_iterator_type__not_same_type(void** state);
void test__slist_same_iterator_type__same_type_not_slist_iterator(void** state);
void test__slist_same_iterator_type__not_same_type_not_slist_iterator(void** state);
/*
 * test _slist_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_slist_get_varg_value_auxiliary)
void test__slist_get_varg_value_auxiliary__null_slist_container(void** state);
void test__slist_get_varg_value_auxiliary__null_node(void** state);
void test__slist_get_varg_value_auxiliary__non_created_slist_containter(void** state);
void test__slist_get_varg_value_auxiliary__c_builtin(void** state);
void test__slist_get_varg_value_auxiliary__cstr(void** state);
void test__slist_get_varg_value_auxiliary__libcstl_builtin(void** state);
void test__slist_get_varg_value_auxiliary__user_define(void** state);
/*
 * test _slist_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_slist_destroy_varg_value_auxiliary)
void test__slist_destroy_varg_value_auxiliary__null_slist_container(void** state);
void test__slist_destroy_varg_value_auxiliary__non_created_slist_container(void** state);
void test__slist_destroy_varg_value_auxiliary__null_node(void** state);
void test__slist_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _slist_init_node_auxiliary
 */
UT_CASE_DECLARATION(_slist_init_node_auxiliary)
void test__slist_init_node_auxiliary__null_slist_container(void** state);
void test__slist_init_node_auxiliary__null_node(void** state);
void test__slist_init_node_auxiliary__non_created_slist_containter(void** state);
void test__slist_init_node_auxiliary__c_builtin(void** state);
void test__slist_init_node_auxiliary__cstr(void** state);
void test__slist_init_node_auxiliary__libcstl_builtin(void** state);
void test__slist_init_node_auxiliary__user_define(void** state);
/*
 * test _slist_transfer
 */
UT_CASE_DECLARATION(_slist_transfer)
void test__slist_transfer__invalid_pos(void** state);
void test__slist_transfer__invalid_begin(void** state);
void test__slist_transfer__invalid_end(void** state);
void test__slist_transfer__invalid_range_not_same_slist(void** state);
void test__slist_transfer__invalid_range_end_before_begin(void** state);
void test__slist_transfer__pos_range_not_same_type(void** state);
void test__slist_transfer__does_nothing_empty_range(void** state);
void test__slist_transfer__successfully_begin_begin(void** state);
void test__slist_transfer__successfully_middle_middle(void** state);
void test__slist_transfer__successfully_end(void** state);
void test__slist_transfer__successfully_middle_all(void** state);
void test__slist_transfer__same_slist_pos_belong_to_range(void** state);
void test__slist_transfer__same_slist_does_nothing_empty_range(void** state);
void test__slist_transfer__same_slist_does_nothing_pos_equa_to_begin(void** state);
void test__slist_transfer__same_slist_does_nothing_pos_equa_to_end(void** state);
void test__slist_transfer__same_slist_begin_middle(void** state);
void test__slist_transfer__same_slist_begin_end(void** state);
void test__slist_transfer__same_slist_middle_begin(void** state);
void test__slist_transfer__same_slist_middle_middle(void** state);
void test__slist_transfer__same_slist_middle_end(void** state);
void test__slist_transfer__same_slist_end_begin(void** state);
void test__slist_transfer__same_slist_end_middle(void** state);
/*
 * test _slist_transfer_after
 */
UT_CASE_DECLARATION(_slist_transfer_after)
void test__slist_transfer_after__invalid_pos(void** state);
void test__slist_transfer_after__invalid_pos_end(void** state);
void test__slist_transfer_after__invalid_begin(void** state);
void test__slist_transfer_after__invalid_end(void** state);
void test__slist_transfer_after__invalid_range_not_same_slist(void** state);
void test__slist_transfer_after__invalid_range_end_before_begin(void** state);
void test__slist_transfer_after__pos_range_not_same_type(void** state);
void test__slist_transfer_after__does_nothing_empty_range(void** state);
void test__slist_transfer_after__successfully_begin_begin(void** state);
void test__slist_transfer_after__successfully_middle_middle(void** state);
void test__slist_transfer_after__successfully_end(void** state);
void test__slist_transfer_after__successfully_middle_all(void** state);
void test__slist_transfer_after__same_slist_pos_belong_to_range(void** state);
void test__slist_transfer_after__same_slist_does_nothing_empty_range(void** state);
void test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_begin(void** state);
void test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_end(void** state);
void test__slist_transfer_after__same_slist_begin_middle(void** state);
void test__slist_transfer_after__same_slist_begin_end(void** state);
void test__slist_transfer_after__same_slist_middle_begin(void** state);
void test__slist_transfer_after__same_slist_middle_middle(void** state);
void test__slist_transfer_after__same_slist_middle_end(void** state);
void test__slist_transfer_after__same_slist_end_begin(void** state);
void test__slist_transfer_after__same_slist_end_middle(void** state);

#define UT_CSTL_SLIST_AUX_CASE\
    UT_SUIT_BEGIN(cstl_slist_aux, test__slist_is_created__null_slist_container),\
    UT_CASE(test__slist_is_created__invalid_type_style),\
    UT_CASE(test__slist_is_created__invalid_type_pointer),\
    UT_CASE(test__slist_is_created__null_node),\
    UT_CASE(test__slist_is_created__uninited_allocator),\
    UT_CASE(test__slist_is_created__successfully),\
    UT_CASE_BEGIN(_slist_is_inited, test__slist_is_inited__null_slist_container),\
    UT_CASE(test__slist_is_inited__invalid_type_styple),\
    UT_CASE(test__slist_is_inited__invalid_type_pointer),\
    UT_CASE(test__slist_is_inited__init_empty),\
    UT_CASE(test__slist_is_inited__init_non_empty),\
    UT_CASE_BEGIN(_slist_iterator_belong_to_slist, test__slist_iterator_belong_to_slist__null_slist_container),\
    UT_CASE(test__slist_iterator_belong_to_slist__non_inited_slist_container),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_container_type),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_iterator_type),\
    UT_CASE(test__slist_iterator_belong_to_slist__invalid_iter_container_pointer),\
    UT_CASE(test__slist_iterator_belong_to_slist__not_belong_to_slist),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_begin),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_middle),\
    UT_CASE(test__slist_iterator_belong_to_slist__belong_to_slist_end),\
    UT_CASE_BEGIN(_slist_same_type, test__slist_same_type__null_first),\
    UT_CASE(test__slist_same_type__null_second),\
    UT_CASE(test__slist_same_type__non_created_first),\
    UT_CASE(test__slist_same_type__non_created_second),\
    UT_CASE(test__slist_same_type__same_c_builtin),\
    UT_CASE(test__slist_same_type__same_c_builtin_dup),\
    UT_CASE(test__slist_same_type__not_same_c_builtin),\
    UT_CASE(test__slist_same_type__same_libcstl_builtin),\
    UT_CASE(test__slist_same_type__same_libcstl_builtin_dup),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_container),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_elem),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_iter),\
    UT_CASE(test__slist_same_type__not_same_libcstl_builtin_string),\
    UT_CASE(test__slist_same_type__not_same_c_libcstl_builtin),\
    UT_CASE(test__slist_same_type__same_user_defined),\
    UT_CASE(test__slist_same_type__same_user_defined_dup),\
    UT_CASE(test__slist_same_type__not_same_c_user_define),\
    UT_CASE(test__slist_same_type__not_same_libcstl_user_define),\
    UT_CASE(test__slist_same_type__same_container),\
    UT_CASE_BEGIN(_slist_same_slist_iterator_type, test__slist_same_slist_iterator_type__null_slist_container),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__slist_same_slist_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__slist_same_slist_iterator_type__same_type_belong_to_slist),\
    UT_CASE(test__slist_same_slist_iterator_type__same_type_not_belong_to_slist),\
    UT_CASE(test__slist_same_slist_iterator_type__not_same_type),\
    UT_CASE_BEGIN(_slist_same_iterator_type, test__slist_same_iterator_type__null_slist_container),\
    UT_CASE(test__slist_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__slist_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__slist_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__slist_same_iterator_type__same_type_belong_to_slist),\
    UT_CASE(test__slist_same_iterator_type__same_type_not_belong_to_slist),\
    UT_CASE(test__slist_same_iterator_type__not_same_type),\
    UT_CASE(test__slist_same_iterator_type__same_type_not_slist_iterator),\
    UT_CASE(test__slist_same_iterator_type__not_same_type_not_slist_iterator),\
    UT_CASE_BEGIN(_slist_get_varg_value_auxiliary, test__slist_get_varg_value_auxiliary__null_slist_container),\
    UT_CASE(test__slist_get_varg_value_auxiliary__null_node),\
    UT_CASE(test__slist_get_varg_value_auxiliary__non_created_slist_containter),\
    UT_CASE(test__slist_get_varg_value_auxiliary__c_builtin),\
    UT_CASE(test__slist_get_varg_value_auxiliary__cstr),\
    UT_CASE(test__slist_get_varg_value_auxiliary__libcstl_builtin),\
    UT_CASE(test__slist_get_varg_value_auxiliary__user_define),\
    UT_CASE_BEGIN(_slist_destroy_varg_value_auxiliary, test__slist_destroy_varg_value_auxiliary__null_slist_container),\
    UT_CASE(test__slist_destroy_varg_value_auxiliary__non_created_slist_container),\
    UT_CASE(test__slist_destroy_varg_value_auxiliary__null_node),\
    UT_CASE(test__slist_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_slist_init_node_auxiliary, test__slist_init_node_auxiliary__null_slist_container),\
    UT_CASE(test__slist_init_node_auxiliary__null_node),\
    UT_CASE(test__slist_init_node_auxiliary__non_created_slist_containter),\
    UT_CASE(test__slist_init_node_auxiliary__c_builtin),\
    UT_CASE(test__slist_init_node_auxiliary__cstr),\
    UT_CASE(test__slist_init_node_auxiliary__libcstl_builtin),\
    UT_CASE(test__slist_init_node_auxiliary__user_define),\
    UT_CASE_BEGIN(_slist_transfer, test__slist_transfer__invalid_pos),\
    UT_CASE(test__slist_transfer__invalid_begin),\
    UT_CASE(test__slist_transfer__invalid_end),\
    UT_CASE(test__slist_transfer__invalid_range_not_same_slist),\
    UT_CASE(test__slist_transfer__invalid_range_end_before_begin),\
    UT_CASE(test__slist_transfer__pos_range_not_same_type),\
    UT_CASE(test__slist_transfer__does_nothing_empty_range),\
    UT_CASE(test__slist_transfer__successfully_begin_begin),\
    UT_CASE(test__slist_transfer__successfully_middle_middle),\
    UT_CASE(test__slist_transfer__successfully_end),\
    UT_CASE(test__slist_transfer__successfully_middle_all),\
    UT_CASE(test__slist_transfer__same_slist_pos_belong_to_range),\
    UT_CASE(test__slist_transfer__same_slist_does_nothing_empty_range),\
    UT_CASE(test__slist_transfer__same_slist_does_nothing_pos_equa_to_begin),\
    UT_CASE(test__slist_transfer__same_slist_does_nothing_pos_equa_to_end),\
    UT_CASE(test__slist_transfer__same_slist_begin_middle),\
    UT_CASE(test__slist_transfer__same_slist_begin_end),\
    UT_CASE(test__slist_transfer__same_slist_middle_begin),\
    UT_CASE(test__slist_transfer__same_slist_middle_middle),\
    UT_CASE(test__slist_transfer__same_slist_middle_end),\
    UT_CASE(test__slist_transfer__same_slist_end_begin),\
    UT_CASE(test__slist_transfer__same_slist_end_middle),\
    UT_CASE_BEGIN(_slist_transfer_after, test__slist_transfer_after__invalid_pos),\
    UT_CASE(test__slist_transfer_after__invalid_pos_end),\
    UT_CASE(test__slist_transfer_after__invalid_begin),\
    UT_CASE(test__slist_transfer_after__invalid_end),\
    UT_CASE(test__slist_transfer_after__invalid_range_not_same_slist),\
    UT_CASE(test__slist_transfer_after__invalid_range_end_before_begin),\
    UT_CASE(test__slist_transfer_after__pos_range_not_same_type),\
    UT_CASE(test__slist_transfer_after__does_nothing_empty_range),\
    UT_CASE(test__slist_transfer_after__successfully_begin_begin),\
    UT_CASE(test__slist_transfer_after__successfully_middle_middle),\
    UT_CASE(test__slist_transfer_after__successfully_end),\
    UT_CASE(test__slist_transfer_after__successfully_middle_all),\
    UT_CASE(test__slist_transfer_after__same_slist_pos_belong_to_range),\
    UT_CASE(test__slist_transfer_after__same_slist_does_nothing_empty_range),\
    UT_CASE(test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_begin),\
    UT_CASE(test__slist_transfer_after__same_slist_does_nothing_pos_equa_to_end),\
    UT_CASE(test__slist_transfer_after__same_slist_begin_middle),\
    UT_CASE(test__slist_transfer_after__same_slist_begin_end),\
    UT_CASE(test__slist_transfer_after__same_slist_middle_begin),\
    UT_CASE(test__slist_transfer_after__same_slist_middle_middle),\
    UT_CASE(test__slist_transfer_after__same_slist_middle_end),\
    UT_CASE(test__slist_transfer_after__same_slist_end_begin),\
    UT_CASE(test__slist_transfer_after__same_slist_end_middle)

#endif /* _UT_CSTL_SLIST_AUX_H_ */

