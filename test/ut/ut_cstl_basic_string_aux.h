#ifndef _UT_CSTL_BASIC_STRING_AUX_H_
#define _UT_CSTL_BASIC_STRING_AUX_H_

UT_SUIT_DECLARATION(cstl_basic_string_aux)

/*
 * test _basic_string_same_type
 */
UT_CASE_DECLARATION(_basic_string_same_type)
void test__basic_string_same_type__null_first(void** state);
void test__basic_string_same_type__null_second(void** state);
void test__basic_string_same_type__non_created_first(void** state);
void test__basic_string_same_type__non_created_second(void** state);
void test__basic_string_same_type__not_same_type_name(void** state);
void test__basic_string_same_type__not_same_type_pointer(void** state);
void test__basic_string_same_type__not_same_type_style(void** state);
void test__basic_string_same_type__not_same_type_style_ex1(void** state);
void test__basic_string_same_type__not_same_type_style_ex2(void** state);
void test__basic_string_same_type__same_type(void** state);
void test__basic_string_same_type__same_type_duplicate_name(void** state);
void test__basic_string_same_type__same_container(void** state);
/*
 * test _basic_string_get_value_string_length
 */
UT_CASE_DECLARATION(_basic_string_get_value_string_length)
void test__basic_string_get_value_string_length__null_basic_string(void** state);
void test__basic_string_get_value_string_length__null_value_string(void** state);
void test__basic_string_get_value_string_length__non_create(void** state);
void test__basic_string_get_value_string_length__c_builtin_empty(void** state);
void test__basic_string_get_value_string_length__c_builtin_non_empty(void** state);
void test__basic_string_get_value_string_length__c_builtin_no_terminal(void** state);
void test__basic_string_get_value_string_length__char_empty(void** state);
void test__basic_string_get_value_string_length__char_non_empty(void** state);
void test__basic_string_get_value_string_length__char_no_terminal(void** state);
void test__basic_string_get_value_string_length__cstr_empty(void** state);
void test__basic_string_get_value_string_length__cstr_non_empty(void** state);
void test__basic_string_get_value_string_length__cstr_no_terminal(void** state);
void test__basic_string_get_value_string_length__libcstl_builtin_empty(void** state);
void test__basic_string_get_value_string_length__libcstl_builtin_non_empty(void** state);
void test__basic_string_get_value_string_length__libcstl_builtin_no_terminal(void** state);
void test__basic_string_get_value_string_length__user_define_empty(void** state);
void test__basic_string_get_value_string_length__user_define_non_empty(void** state);
void test__basic_string_get_value_string_length__user_define_no_terminal(void** state);
/*
 * test _basic_string_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_get_varg_value_auxiliary)
void test__basic_string_get_varg_value_auxiliary__null_basic_string_container(void** state);
void test__basic_string_get_varg_value_auxiliary__null_varg(void** state);
void test__basic_string_get_varg_value_auxiliary__non_created(void** state);
void test__basic_string_get_varg_value_auxiliary__successfully(void** state);
/*
 * test _basic_string_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_destroy_varg_value_auxiliary)
void test__basic_string_destroy_varg_value_auxiliary__null_basic_string_container(void** state);
void test__basic_string_destroy_varg_value_auxiliary__null_varg(void** state);
void test__basic_string_destroy_varg_value_auxiliary__non_created(void** state);
void test__basic_string_destroy_varg_value_auxiliary__successfully(void** state);
/*
 * test _basic_string_is_created
 */
UT_CASE_DECLARATION(_basic_string_is_created)
void test__basic_string_is_created__null_basic_string_container(void** state);
void test__basic_string_is_created__non_created_invalid_pby_string(void** state);
void test__basic_string_is_created__non_created_invalid_type_style(void** state);
void test__basic_string_is_created__created(void** state);
/*
 * test _basic_string_is_inited
 */
UT_CASE_DECLARATION(_basic_string_is_inited)
void test__basic_string_is_inited__null_basic_string_container(void** state);
void test__basic_string_is_inited__non_inited_pby_string_null(void** state);
void test__basic_string_is_inited__non_inited_leaked(void** state);
void test__basic_string_is_inited__non_inited_invalid_type_style(void** state);
void test__basic_string_is_inited__inited_empty(void** state);
void test__basic_string_is_inited__inited_non_empty(void** state);
/*
 * test _basic_string_init_elem_range_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_init_elem_range_auxiliary)
void test__basic_string_init_elem_range_auxiliary__null_basic_string_containter(void** state);
void test__basic_string_init_elem_range_auxiliary__null_pby_string(void** state);
void test__basic_string_init_elem_range_auxiliary__non_created(void** state);
void test__basic_string_init_elem_range_auxiliary__successfully_int(void** state);
void test__basic_string_init_elem_range_auxiliary__successfully_cstr(void** state);
void test__basic_string_init_elem_range_auxiliary__successfully_iterator(void** state);
void test__basic_string_init_elem_range_auxiliary__successfully_container(void** state);
/*
 * test _basic_string_detach
 */
UT_CASE_DECLARATION(_basic_string_detach)
void test__basic_string_detach__null(void** state);
void test__basic_string_detach__non_init(void** state);
void test__basic_string_detach__non_sharable(void** state);
void test__basic_string_detach__sharable(void** state);
/*
 * test _basic_string_is_shared
 */
UT_CASE_DECLARATION(_basic_string_is_shared)
void test__basic_string_is_shared__null(void** state);
void test__basic_string_is_shared__non_inited(void** state);
void test__basic_string_is_shared__shared(void** state);
void test__basic_string_is_shared__not_shared(void** state);
/*
 * test _basic_string_clone_representation
 */
UT_CASE_DECLARATION(_basic_string_clone_representation)
void test__basic_string_clone_representation__null(void** state);
void test__basic_string_clone_representation__non_inited(void** state);
void test__basic_string_clone_representation__c_builtin_length_0(void** state);
void test__basic_string_clone_representation__c_builtin_length_not_0(void** state);
void test__basic_string_clone_representation__cstr_length_0(void** state);
void test__basic_string_clone_representation__cstr_length_not_0(void** state);
void test__basic_string_clone_representation__cstl_builtin_length_0(void** state);
void test__basic_string_clone_representation__cstl_builtin_length_not_0(void** state);
void test__basic_string_clone_representation__user_define_length_0(void** state);
void test__basic_string_clone_representation__user_define_length_not_0(void** state);
/*
 * test _basic_string_iterator_belong_to_basic_string
 */
UT_CASE_DECLARATION(_basic_string_iterator_belong_to_basic_string)
void test__basic_string_iterator_belong_to_basic_string__null_container_pointer(void** state);
void test__basic_string_iterator_belong_to_basic_string__non_inited_basic_string_container(void** state);
void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_container_type(void** state);
void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_iterator_type(void** state);
void test__basic_string_iterator_belong_to_basic_string__invalid_iterator_different_container(void** state);
void test__basic_string_iterator_belong_to_basic_string__less_than_begin(void** state);
void test__basic_string_iterator_belong_to_basic_string__within_basic_string(void** state);
void test__basic_string_iterator_belong_to_basic_string__end_iterator(void** state);
void test__basic_string_iterator_belong_to_basic_string__greater_than_end(void** state);
/*
 * test _basic_string_same_iterator_type
 */
UT_CASE_DECLARATION(_basic_string_same_iterator_type)
void test__basic_string_same_iterator_type__null_basic_string_container(void** state);
void test__basic_string_same_iterator_type__invalid_iterator_null_container(void** state);
void test__basic_string_same_iterator_type__invalid_iterator_container_type(void** state);
void test__basic_string_same_iterator_type__invalid_iterator_iterator_type(void** state);
void test__basic_string_same_iterator_type__same_type_belong_to_basic_string(void** state);
void test__basic_string_same_iterator_type__same_type_not_belong_to_basic_string(void** state);
void test__basic_string_same_iterator_type__not_same_type(void** state);
void test__basic_string_same_iterator_type__same_type_not_basic_string_iterator(void** state);
void test__basic_string_same_iterator_type__not_same_type_not_basic_string_iterator(void** state);
/*
 * test _basic_string_copy_substring_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_copy_substring_auxiliary)
void test__basic_string_copy_substring_auxiliary__null_bstr(void** state);
void test__basic_string_copy_substring_auxiliary__non_created(void** state);
void test__basic_string_copy_substring_auxiliary__null_dest(void** state);
void test__basic_string_copy_substring_auxiliary__null_src(void** state);
void test__basic_string_copy_substring_auxiliary__invalid_len(void** state);
void test__basic_string_copy_substring_auxiliary__empty(void** state);
void test__basic_string_copy_substring_auxiliary__non_empty(void** state);
void test__basic_string_copy_substring_auxiliary__cstr(void** state);
void test__basic_string_copy_substring_auxiliary__libcstl(void** state);
void test__basic_string_copy_substring_auxiliary__user_define(void** state);
/*
 * test _basic_string_copy_subcstr_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_copy_subcstr_auxiliary)
void test__basic_string_copy_subcstr_auxiliary__null_bstr(void** state);
void test__basic_string_copy_subcstr_auxiliary__non_created(void** state);
void test__basic_string_copy_subcstr_auxiliary__null_dest(void** state);
void test__basic_string_copy_subcstr_auxiliary__null_src(void** state);
void test__basic_string_copy_subcstr_auxiliary__invalid_len(void** state);
void test__basic_string_copy_subcstr_auxiliary__empty(void** state);
void test__basic_string_copy_subcstr_auxiliary__non_empty(void** state);
void test__basic_string_copy_subcstr_auxiliary__cstr(void** state);
void test__basic_string_copy_subcstr_auxiliary__libcstl(void** state);
void test__basic_string_copy_subcstr_auxiliary__user_define(void** state);
void test__basic_string_copy_subcstr_auxiliary__include_terminator(void** state);
/*
 * test _basic_string_copy_range_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_copy_range_auxiliary)
void test__basic_string_copy_range_auxiliary__null_bstr(void** state);
void test__basic_string_copy_range_auxiliary__non_created(void** state);
void test__basic_string_copy_range_auxiliary__null_dest(void** state);
void test__basic_string_copy_range_auxiliary__invalid_range(void** state);
void test__basic_string_copy_range_auxiliary__empty(void** state);
void test__basic_string_copy_range_auxiliary__non_empty(void** state);
void test__basic_string_copy_range_auxiliary__cstr(void** state);
void test__basic_string_copy_range_auxiliary__libcstl(void** state);
void test__basic_string_copy_range_auxiliary__user_define(void** state);
/*
 * test _basic_string_copy_elem_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_copy_elem_auxiliary)
void test__basic_string_copy_elem_auxiliary__null_bstr(void** state);
void test__basic_string_copy_elem_auxiliary__non_created(void** state);
void test__basic_string_copy_elem_auxiliary__null_dest(void** state);
void test__basic_string_copy_elem_auxiliary__invalid_len(void** state);
void test__basic_string_copy_elem_auxiliary__empty(void** state);
void test__basic_string_copy_elem_auxiliary__non_empty(void** state);
void test__basic_string_copy_elem_auxiliary__cstr(void** state);
void test__basic_string_copy_elem_auxiliary__libcstl(void** state);
void test__basic_string_copy_elem_auxiliary__user_define(void** state);
/*
 * test _basic_string_copy_substring_backward_auxiliary
 */
UT_CASE_DECLARATION(_basic_string_copy_substring_backward_auxiliary)
void test__basic_string_copy_substring_backward_auxiliary__null_bstr(void** state);
void test__basic_string_copy_substring_backward_auxiliary__non_created(void** state);
void test__basic_string_copy_substring_backward_auxiliary__null_dest(void** state);
void test__basic_string_copy_substring_backward_auxiliary__null_src(void** state);
void test__basic_string_copy_substring_backward_auxiliary__invalid_len(void** state);
void test__basic_string_copy_substring_backward_auxiliary__empty(void** state);
void test__basic_string_copy_substring_backward_auxiliary__non_empty(void** state);
void test__basic_string_copy_substring_backward_auxiliary__cstr(void** state);
void test__basic_string_copy_substring_backward_auxiliary__libcstl(void** state);
void test__basic_string_copy_substring_backward_auxiliary__user_define(void** state);

#define UT_CSTL_BASIC_STRING_AUX_CASE\
    UT_SUIT_BEGIN(cstl_basic_string_aux, test__basic_string_is_created__null_basic_string_container),\
    UT_CASE(test__basic_string_is_created__non_created_invalid_pby_string),\
    UT_CASE(test__basic_string_is_created__non_created_invalid_type_style),\
    UT_CASE(test__basic_string_is_created__created),\
    UT_CASE_BEGIN(_basic_string_is_inited, test__basic_string_is_inited__null_basic_string_container),\
    UT_CASE(test__basic_string_is_inited__non_inited_pby_string_null),\
    UT_CASE(test__basic_string_is_inited__non_inited_leaked),\
    UT_CASE(test__basic_string_is_inited__non_inited_invalid_type_style),\
    UT_CASE(test__basic_string_is_inited__inited_empty),\
    UT_CASE(test__basic_string_is_inited__inited_non_empty),\
    UT_CASE_BEGIN(_basic_string_same_type, test__basic_string_same_type__null_first),\
    UT_CASE(test__basic_string_same_type__null_second),\
    UT_CASE(test__basic_string_same_type__non_created_first),\
    UT_CASE(test__basic_string_same_type__non_created_second),\
    UT_CASE(test__basic_string_same_type__not_same_type_name),\
    UT_CASE(test__basic_string_same_type__not_same_type_pointer),\
    UT_CASE(test__basic_string_same_type__not_same_type_style),\
    UT_CASE(test__basic_string_same_type__not_same_type_style_ex1),\
    UT_CASE(test__basic_string_same_type__not_same_type_style_ex2),\
    UT_CASE(test__basic_string_same_type__same_type),\
    UT_CASE(test__basic_string_same_type__same_type_duplicate_name),\
    UT_CASE(test__basic_string_same_type__same_container),\
    UT_CASE_BEGIN(_basic_string_get_varg_value_auxiliary,\
        test__basic_string_get_varg_value_auxiliary__null_basic_string_container),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__null_varg),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__non_created),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_basic_string_destroy_varg_value_auxiliary,\
        test__basic_string_destroy_varg_value_auxiliary__null_basic_string_container),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__non_created),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_basic_string_init_elem_range_auxiliary, test__basic_string_init_elem_range_auxiliary__null_basic_string_containter),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__null_pby_string),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__non_created),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__successfully_int),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__successfully_cstr),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__successfully_iterator),\
    UT_CASE(test__basic_string_init_elem_range_auxiliary__successfully_container),\
    UT_CASE_BEGIN(_basic_string_detach, test__basic_string_detach__null),\
    UT_CASE(test__basic_string_detach__non_init),\
    UT_CASE(test__basic_string_detach__non_sharable),\
    UT_CASE(test__basic_string_detach__sharable),\
    UT_CASE_BEGIN(_basic_string_get_value_string_length, test__basic_string_get_value_string_length__null_basic_string),\
    UT_CASE(test__basic_string_get_value_string_length__null_value_string),\
    UT_CASE(test__basic_string_get_value_string_length__non_create),\
    UT_CASE(test__basic_string_get_value_string_length__c_builtin_empty),\
    UT_CASE(test__basic_string_get_value_string_length__c_builtin_non_empty),\
    UT_CASE(test__basic_string_get_value_string_length__c_builtin_no_terminal),\
    UT_CASE(test__basic_string_get_value_string_length__char_empty),\
    UT_CASE(test__basic_string_get_value_string_length__char_non_empty),\
    UT_CASE(test__basic_string_get_value_string_length__char_no_terminal),\
    UT_CASE(test__basic_string_get_value_string_length__cstr_empty),\
    UT_CASE(test__basic_string_get_value_string_length__cstr_non_empty),\
    UT_CASE(test__basic_string_get_value_string_length__cstr_no_terminal),\
    UT_CASE(test__basic_string_get_value_string_length__libcstl_builtin_empty),\
    UT_CASE(test__basic_string_get_value_string_length__libcstl_builtin_non_empty),\
    UT_CASE(test__basic_string_get_value_string_length__libcstl_builtin_no_terminal),\
    UT_CASE(test__basic_string_get_value_string_length__user_define_empty),\
    UT_CASE(test__basic_string_get_value_string_length__user_define_non_empty),\
    UT_CASE(test__basic_string_get_value_string_length__user_define_no_terminal),\
    UT_CASE_BEGIN(_basic_string_is_shared, test__basic_string_is_shared__null),\
    UT_CASE(test__basic_string_is_shared__non_inited),\
    UT_CASE(test__basic_string_is_shared__shared),\
    UT_CASE(test__basic_string_is_shared__not_shared),\
    UT_CASE_BEGIN(_basic_string_clone_representation, test__basic_string_clone_representation__null),\
    UT_CASE(test__basic_string_clone_representation__non_inited),\
    UT_CASE(test__basic_string_clone_representation__c_builtin_length_0),\
    UT_CASE(test__basic_string_clone_representation__c_builtin_length_not_0),\
    UT_CASE(test__basic_string_clone_representation__cstr_length_0),\
    UT_CASE(test__basic_string_clone_representation__cstr_length_not_0),\
    UT_CASE(test__basic_string_clone_representation__cstl_builtin_length_0),\
    UT_CASE(test__basic_string_clone_representation__cstl_builtin_length_not_0),\
    UT_CASE(test__basic_string_clone_representation__user_define_length_0),\
    UT_CASE(test__basic_string_clone_representation__user_define_length_not_0),\
    UT_CASE_BEGIN(_basic_string_iterator_belong_to_basic_string, test__basic_string_iterator_belong_to_basic_string__null_container_pointer),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__non_inited_basic_string_container),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__invalid_iterator_different_container),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__less_than_begin),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__within_basic_string),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__end_iterator),\
    UT_CASE(test__basic_string_iterator_belong_to_basic_string__greater_than_end),\
    UT_CASE_BEGIN(_basic_string_same_iterator_type, test__basic_string_same_iterator_type__null_basic_string_container),\
    UT_CASE(test__basic_string_same_iterator_type__invalid_iterator_null_container),\
    UT_CASE(test__basic_string_same_iterator_type__invalid_iterator_container_type),\
    UT_CASE(test__basic_string_same_iterator_type__invalid_iterator_iterator_type),\
    UT_CASE(test__basic_string_same_iterator_type__same_type_belong_to_basic_string),\
    UT_CASE(test__basic_string_same_iterator_type__same_type_not_belong_to_basic_string),\
    UT_CASE(test__basic_string_same_iterator_type__not_same_type),\
    UT_CASE(test__basic_string_same_iterator_type__same_type_not_basic_string_iterator),\
    UT_CASE(test__basic_string_same_iterator_type__not_same_type_not_basic_string_iterator),\
    UT_CASE_BEGIN(_basic_string_copy_substring_auxiliary, test__basic_string_copy_substring_auxiliary__null_bstr),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__non_created),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__null_dest),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__null_src),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__invalid_len),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__empty),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__non_empty),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__cstr),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__libcstl),\
    UT_CASE(test__basic_string_copy_substring_auxiliary__user_define),\
    UT_CASE_BEGIN(_basic_string_copy_substring_backward_auxiliary, test__basic_string_copy_substring_backward_auxiliary__null_bstr),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__non_created),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__null_dest),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__null_src),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__invalid_len),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__empty),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__non_empty),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__cstr),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__libcstl),\
    UT_CASE(test__basic_string_copy_substring_backward_auxiliary__user_define),\
    UT_CASE_BEGIN(_basic_string_copy_subcstr_auxiliary, test__basic_string_copy_subcstr_auxiliary__null_bstr),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__non_created),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__null_dest),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__null_src),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__invalid_len),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__empty),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__non_empty),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__cstr),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__libcstl),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__user_define),\
    UT_CASE(test__basic_string_copy_subcstr_auxiliary__include_terminator),\
    UT_CASE_BEGIN(_basic_string_copy_range_auxiliary, test__basic_string_copy_range_auxiliary__null_bstr),\
    UT_CASE(test__basic_string_copy_range_auxiliary__non_created),\
    UT_CASE(test__basic_string_copy_range_auxiliary__null_dest),\
    UT_CASE(test__basic_string_copy_range_auxiliary__invalid_range),\
    UT_CASE(test__basic_string_copy_range_auxiliary__empty),\
    UT_CASE(test__basic_string_copy_range_auxiliary__non_empty),\
    UT_CASE(test__basic_string_copy_range_auxiliary__cstr),\
    UT_CASE(test__basic_string_copy_range_auxiliary__libcstl),\
    UT_CASE(test__basic_string_copy_range_auxiliary__user_define),\
    UT_CASE_BEGIN(_basic_string_copy_elem_auxiliary, test__basic_string_copy_elem_auxiliary__null_bstr),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__non_created),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__null_dest),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__invalid_len),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__empty),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__non_empty),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__cstr),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__libcstl),\
    UT_CASE(test__basic_string_copy_elem_auxiliary__user_define)

#endif /* _UT_CSTL_BASIC_STRING_AUX_H_ */

