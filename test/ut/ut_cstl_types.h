#ifndef _UT_CSTL_TYPES_H_
#define _UT_CSTL_TYPES_H_

UT_SUIT_DECLARATION(cstl_types)
/*
 * test _type_init_default
 */
UT_CASE_DECLARATION(_type_init_default)
void test__type_init_default__null_input(void** state);
void test__type_init_default__null_output(void** state);
void test__type_init_default__ok(void** state);
/*
 * test _type_less_default
 */
UT_CASE_DECLARATION(_type_less_default)
void test__type_less_defaule__null_first(void** state);
void test__type_less_defaule__null_second(void** state);
void test__type_less_defaule__null_output(void** state);
void test__type_less_defaule__less(void** state);
void test__type_less_defaule__equal(void** state);
void test__type_less_defaule__greater(void** state);
/*
 * test _type_copy_default
 */
UT_CASE_DECLARATION(_type_copy_default)
void test__type_copy_defaule__null_first(void** state);
void test__type_copy_defaule__null_second(void** state);
void test__type_copy_defaule__null_output(void** state);
void test__type_copy_defaule__ok(void** state);
/*
 * test _type_destroy_default
 */
UT_CASE_DECLARATION(_type_destroy_default)
void test__type_destroy_default__null_input(void** state);
void test__type_destroy_default__null_output(void** state);
void test__type_destroy_default__ok(void** state);
/*
 * test _type_get_varg_value
 */
UT_CASE_DECLARATION(_type_get_varg_value)
void test__type_get_varg_value__null_typeinof(void** state);
void test__type_get_varg_value__invalid_typeinfo(void** state);
void test__type_get_varg_value__invalid_typeinfo_style(void** state);
void test__type_get_varg_value__invalid_typeinfo_style2(void** state);
void test__type_get_varg_value__null_output(void** state);
void test__type_get_varg_value__char(void** state);
void test__type_get_varg_value__uchar(void** state);
void test__type_get_varg_value__short(void** state);
void test__type_get_varg_value__ushort(void** state);
void test__type_get_varg_value__int(void** state);
void test__type_get_varg_value__uint(void** state);
void test__type_get_varg_value__long(void** state);
void test__type_get_varg_value__ulong(void** state);
void test__type_get_varg_value__float(void** state);
void test__type_get_varg_value__double(void** state);
void test__type_get_varg_value__ldouble(void** state);
void test__type_get_varg_value__bool(void** state);
void test__type_get_varg_value__cstr(void** state);
void test__type_get_varg_value__invalid_c_builtin(void** state);
void test__type_get_varg_value__user_define(void** state);
void test__type_get_varg_value__cstl_builtin(void** state);
/*
 * test _type_get_elem_typename
 */
UT_CASE_DECLARATION(_type_get_elem_typename)
void test__type_get_elem_typename__null_typename(void** state);
void test__type_get_elem_typename__null_elemtypename(void** state);
void test__type_get_elem_typename__iterator(void** state);
void test__type_get_elem_typename__string(void** state);
void test__type_get_elem_typename__invliad_typename(void** state);
void test__type_get_elem_typename__container(void** state);
/*
 * test _type_is_same
 */
UT_CASE_DECLARATION(_type_is_same)
void test__type_is_same__null_typename1(void** state);
void test__type_is_same__null_typename2(void** state);
void test__type_is_same__c_c_same(void** state);
void test__type_is_same__c_c_duplicate(void** state);
void test__type_is_same__c_c_not_same(void** state);
void test__type_is_same__c_user_not_same(void** state);
void test__type_is_same__c_string_not_same(void** state);
void test__type_is_same__c_iterator_not_same(void** state);
void test__type_is_same__c_cstl_not_same(void** state);
void test__type_is_same__user_user_same(void** state);
void test__type_is_same__user_user_not_same(void** state);
void test__type_is_same__user_user_duplicate(void** state);
void test__type_is_same__user_cstl_not_same(void** state);
void test__type_is_same__string_iterator_not_same(void** state);
void test__type_is_same__cstl_cstl_elem_not_same(void** state);
void test__type_is_same__cstl_cstl_container_not_same(void** state);
void test__type_is_same__cstl_cstl_seq_rel_not_same(void** state);
void test__type_is_same__cstl_cstl_first_not_same(void** state);
void test__type_is_same__cstl_cstl_second_not_same(void** state);
void test__type_is_same__cstl_cstl_rel_not_same(void** state);
void test__type_is_same__cstl_cstl_same(void** state);
void test__type_is_same__cstl_cstl_same_complex(void** state);
void test__type_is_same__cstl_cstl_invalid(void** state);
/*
 * test _type_is_same_ex
 */
UT_CASE_DECLARATION(_type_is_same_ex)
void test__type_is_same_ex__null_first(void** state);
void test__type_is_same_ex__null_second(void** state);
void test__type_is_same_ex__same_typeinfo(void** state);
void test__type_is_same_ex__not_same_type(void** state);
void test__type_is_same_ex__not_same_style(void** state);
void test__type_is_same_ex__same(void** state);
/*
 * test _type_get_type
 */
UT_CASE_DECLARATION(_type_get_type)
void test__type_get_type__null_typeinfo(void** state);
void test__type_get_type__null_typename(void** state);
void test__type_get_type__invalid(void** state);
void test__type_get_type__c_builtin(void** state);
void test__type_get_type__user_define(void** state);
void test__type_get_type__cstl_iterator(void** state);
void test__type_get_type__cstl_container(void** state);
/*
 * test _type_get_type_pair
 */
UT_CASE_DECLARATION(_type_get_type_pair)
void test__type_get_type_pair__null_first(void** state);
void test__type_get_type_pair__null_second(void** state);
void test__type_get_type_pair__null_typename(void** state);
void test__type_get_type_pair__c_c(void** state);
void test__type_get_type_pair__c_user(void** state);
void test__type_get_type_pair__c_iterator(void** state);
void test__type_get_type_pair__c_seq(void** state);
void test__type_get_type_pair__c_rel(void** state);
void test__type_get_type_pair__usr_usr(void** state);
void test__type_get_type_pair__usr_string(void** state);
void test__type_get_type_pair__seq_seq(void** state);
void test__type_get_type_pair__seq_rel(void** state);
void test__type_get_type_pair__rel_rel(void** state);
void test__type_get_type_pair__complex(void** state);
void test__type_get_type_pair__invalid(void** state);
/*
 * test _type_duplicate
 */
UT_CASE_DECLARATION(_type_duplicate)
void test__type_duplicate__null_typename1(void** state);
void test__type_duplicate__null_typename2(void** state);
void test__type_duplicate__size_not_equal(void** state);
void test__type_duplicate__all_not_registered(void** state);
void test__type_duplicate__all_registered(void** state);
void test__type_duplicate__all_registered_same(void** state);
void test__type_duplicate__duplicate_first(void** state);
void test__type_duplicate__duplicate_second(void** state);
/*
 * test _type_register
 */
UT_CASE_DECLARATION(_type_register)
void test__type_register__null_typename(void** state);
void test__type_register__registered(void** state);
void test__type_register__register_default(void** state);
void test__type_register__register(void** state);

#define UT_CSTL_TYPES_CASE\
    UT_SUIT_BEGIN(cstl_types, test__type_init_default__null_input),\
    UT_CASE(test__type_init_default__null_output),\
    UT_CASE(test__type_init_default__ok),\
    UT_CASE_BEGIN(_type_less_default, test__type_less_defaule__null_first),\
    UT_CASE(test__type_less_defaule__null_second),\
    UT_CASE(test__type_less_defaule__null_output),\
    UT_CASE(test__type_less_defaule__less),\
    UT_CASE(test__type_less_defaule__equal),\
    UT_CASE(test__type_less_defaule__greater),\
    UT_CASE_BEGIN(_type_copy_default, test__type_copy_defaule__null_first),\
    UT_CASE(test__type_copy_defaule__null_second),\
    UT_CASE(test__type_copy_defaule__null_output),\
    UT_CASE(test__type_copy_defaule__ok),\
    UT_CASE_BEGIN(_type_destroy_default, test__type_destroy_default__null_input),\
    UT_CASE(test__type_destroy_default__null_output),\
    UT_CASE(test__type_destroy_default__ok),\
    UT_CASE_BEGIN(_type_get_varg_value, test__type_get_varg_value__null_typeinof),\
    UT_CASE(test__type_get_varg_value__invalid_typeinfo),\
    UT_CASE(test__type_get_varg_value__invalid_typeinfo_style),\
    UT_CASE(test__type_get_varg_value__invalid_typeinfo_style2),\
    UT_CASE(test__type_get_varg_value__null_output),\
    UT_CASE(test__type_get_varg_value__char),\
    UT_CASE(test__type_get_varg_value__uchar),\
    UT_CASE(test__type_get_varg_value__short),\
    UT_CASE(test__type_get_varg_value__ushort),\
    UT_CASE(test__type_get_varg_value__int),\
    UT_CASE(test__type_get_varg_value__uint),\
    UT_CASE(test__type_get_varg_value__long),\
    UT_CASE(test__type_get_varg_value__ulong),\
    UT_CASE(test__type_get_varg_value__float),\
    UT_CASE(test__type_get_varg_value__double),\
    UT_CASE(test__type_get_varg_value__ldouble),\
    UT_CASE(test__type_get_varg_value__bool),\
    UT_CASE(test__type_get_varg_value__cstr),\
    UT_CASE(test__type_get_varg_value__invalid_c_builtin),\
    UT_CASE(test__type_get_varg_value__user_define),\
    UT_CASE(test__type_get_varg_value__cstl_builtin),\
    UT_CASE_BEGIN(_type_get_elem_typename, test__type_get_elem_typename__null_typename),\
    UT_CASE(test__type_get_elem_typename__null_elemtypename),\
    UT_CASE(test__type_get_elem_typename__iterator),\
    UT_CASE(test__type_get_elem_typename__string),\
    UT_CASE(test__type_get_elem_typename__invliad_typename),\
    UT_CASE(test__type_get_elem_typename__container),\
    UT_CASE_BEGIN(_type_is_same, test__type_is_same__null_typename1),\
    UT_CASE(test__type_is_same__null_typename2),\
    UT_CASE(test__type_is_same__c_c_same),\
    UT_CASE(test__type_is_same__c_c_duplicate),\
    UT_CASE(test__type_is_same__c_c_not_same),\
    UT_CASE(test__type_is_same__c_user_not_same),\
    UT_CASE(test__type_is_same__c_string_not_same),\
    UT_CASE(test__type_is_same__c_iterator_not_same),\
    UT_CASE(test__type_is_same__c_cstl_not_same),\
    UT_CASE(test__type_is_same__user_user_same),\
    UT_CASE(test__type_is_same__user_user_not_same),\
    UT_CASE(test__type_is_same__user_user_duplicate),\
    UT_CASE(test__type_is_same__user_cstl_not_same),\
    UT_CASE(test__type_is_same__string_iterator_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_elem_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_container_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_seq_rel_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_first_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_second_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_rel_not_same),\
    UT_CASE(test__type_is_same__cstl_cstl_same),\
    UT_CASE(test__type_is_same__cstl_cstl_same_complex),\
    UT_CASE(test__type_is_same__cstl_cstl_invalid),\
    UT_CASE_BEGIN(_type_is_same_ex, test__type_is_same_ex__null_first),\
    UT_CASE(test__type_is_same_ex__null_second),\
    UT_CASE(test__type_is_same_ex__same_typeinfo),\
    UT_CASE(test__type_is_same_ex__not_same_type),\
    UT_CASE(test__type_is_same_ex__not_same_style),\
    UT_CASE(test__type_is_same_ex__same),\
    UT_CASE_BEGIN(_type_get_type, test__type_get_type__null_typeinfo),\
    UT_CASE(test__type_get_type__null_typename),\
    UT_CASE(test__type_get_type__invalid),\
    UT_CASE(test__type_get_type__c_builtin),\
    UT_CASE(test__type_get_type__user_define),\
    UT_CASE(test__type_get_type__cstl_iterator),\
    UT_CASE(test__type_get_type__cstl_container),\
    UT_CASE_BEGIN(_type_get_type_pair, test__type_get_type_pair__null_first),\
    UT_CASE(test__type_get_type_pair__null_second),\
    UT_CASE(test__type_get_type_pair__null_typename),\
    UT_CASE(test__type_get_type_pair__c_c),\
    UT_CASE(test__type_get_type_pair__c_user),\
    UT_CASE(test__type_get_type_pair__c_iterator),\
    UT_CASE(test__type_get_type_pair__c_seq),\
    UT_CASE(test__type_get_type_pair__c_rel),\
    UT_CASE(test__type_get_type_pair__usr_usr),\
    UT_CASE(test__type_get_type_pair__usr_string),\
    UT_CASE(test__type_get_type_pair__seq_seq),\
    UT_CASE(test__type_get_type_pair__seq_rel),\
    UT_CASE(test__type_get_type_pair__rel_rel),\
    UT_CASE(test__type_get_type_pair__complex),\
    UT_CASE(test__type_get_type_pair__invalid),\
    UT_CASE_BEGIN(_type_duplicate, test__type_duplicate__null_typename1),\
    UT_CASE(test__type_duplicate__null_typename2),\
    UT_CASE(test__type_duplicate__size_not_equal),\
    UT_CASE(test__type_duplicate__all_not_registered),\
    UT_CASE(test__type_duplicate__all_registered),\
    UT_CASE(test__type_duplicate__all_registered_same),\
    UT_CASE(test__type_duplicate__duplicate_first),\
    UT_CASE(test__type_duplicate__duplicate_second),\
    UT_CASE_BEGIN(_type_register, test__type_register__null_typename),\
    UT_CASE(test__type_register__registered),\
    UT_CASE(test__type_register__register_default),\
    UT_CASE(test__type_register__register),\

#endif /* _UT_CSTL_TYPES_H_ */

