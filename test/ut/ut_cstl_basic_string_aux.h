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

#define UT_CSTL_BASIC_STRING_AUX_CASE\
    UT_SUIT_BEGIN(cstl_basic_string_aux, test__basic_string_same_type__null_first),\
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
    UT_CASE_BEGIN(_basic_string_get_value_string_length, test__basic_string_get_value_string_length__null_basic_string),\
    UT_CASE(test__basic_string_get_value_string_length__null_value_string),\
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
    UT_CASE_BEGIN(_basic_string_get_varg_value_auxiliary,\
        test__basic_string_get_varg_value_auxiliary__null_basic_string_container),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__null_varg),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__non_created),\
    UT_CASE(test__basic_string_get_varg_value_auxiliary__successfully),\
    UT_CASE_BEGIN(_basic_string_destroy_varg_value_auxiliary,\
        test__basic_string_destroy_varg_value_auxiliary__null_basic_string_container),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__non_created),\
    UT_CASE(test__basic_string_destroy_varg_value_auxiliary__successfully)

#endif /* _UT_CSTL_BASIC_STRING_AUX_H_ */

