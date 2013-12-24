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
/*
 * test all types
 */
UT_CASE_DECLARATION(all_types)
/* C_BUILTIN */
void test__all_types__char(void** state);
void test__all_types__signed_char(void** state);
void test__all_types__unsigned_char(void** state);
void test__all_types__short(void** state);
void test__all_types__signed_short(void** state);
void test__all_types__short_int(void** state);
void test__all_types__signed_short_int(void** state);
void test__all_types__unsigned_short(void** state);
void test__all_types__unsigned_short_int(void** state);
void test__all_types__int(void** state);
void test__all_types__signed(void** state);
void test__all_types__signed_int(void** state);
void test__all_types__unsigned(void** state);
void test__all_types__unsigned_int(void** state);
void test__all_types__long(void** state);
void test__all_types__signed_long(void** state);
void test__all_types__long_int(void** state);
void test__all_types__signed_long_int(void** state);
void test__all_types__unsigned_long(void** state);
void test__all_types__unsigned_long_int(void** state);
void test__all_types__float(void** state);
void test__all_types__double(void** state);
void test__all_types__long_double(void** state);
void test__all_types__cstr(void** state);
void test__all_types__pointer(void** state);
/* USER_DEFINE */
void test__all_types__struct(void** state);
void test__all_types__enum(void** state);
void test__all_types__union(void** state);
void test__all_types__id(void** state);
/* SEQUENCE */
void test__all_types__vector(void** state);
void test__all_types__list(void** state);
void test__all_types__slist(void** state);
void test__all_types__deque(void** state);
void test__all_types__queue(void** state);
void test__all_types__stack(void** state);
void test__all_types__priority_queue(void** state);
void test__all_types__set(void** state);
void test__all_types__multiset(void** state);
void test__all_types__hash_set(void** state);
void test__all_types__hash_multiset(void** state);
void test__all_types__basic_string(void** state);
/* RELATION */
void test__all_types__map(void** state);
void test__all_types__multimap(void** state);
void test__all_types__hash_map(void** state);
void test__all_types__hash_multimap(void** state);
void test__all_types__pair(void** state);
/* string_t, bool_t, range_t */
void test__all_types__string(void** state);
void test__all_types__cstl_bool(void** state);
void test__all_types__range(void** state);
/* ITERATOR */
void test__all_types__iterator(void** state);
void test__all_types__vector_iterator(void** state);
void test__all_types__list_iterator(void** state);
void test__all_types__slist_iterator(void** state);
void test__all_types__deque_iterator(void** state);
void test__all_types__set_iterator(void** state);
void test__all_types__map_iterator(void** state);
void test__all_types__multiset_iterator(void** state);
void test__all_types__multimap_iterator(void** state);
void test__all_types__hash_set_iterator(void** state);
void test__all_types__hash_map_iterator(void** state);
void test__all_types__hash_multiset_iterator(void** state);
void test__all_types__hash_multimap_iterator(void** state);
void test__all_types__string_iterator(void** state);
void test__all_types__input_iterator(void** state);
void test__all_types__output_iterator(void** state);
void test__all_types__forward_iterator(void** state);
void test__all_types__bidirectional_iterator(void** state);
void test__all_types__random_access_iterator(void** state);
void test__all_types__basic_string_iterator(void** state);
#ifndef _MSC_VER
void test__all_types__bool(void** state);
void test__all_types__long_long(void** state);
void test__all_types__long_long_int(void** state);
void test__all_types__signed_long_long(void** state);
void test__all_types__signed_long_long_int(void** state);
void test__all_types__unsigned_long_long(void** state);
void test__all_types__unsigned_long_long_int(void** state);
#endif
/*
 * test void* usage
 */
UT_CASE_DECLARATION(pointer_usage)
void test__pointer_usage__create(void** state);
void test__pointer_usage__init_n(void** state);
void test__pointer_usage__init_elem(void** state);
void test__pointer_usage__iterator(void** state);
void test__pointer_usage__at(void** state);
void test__pointer_usage__copy(void** state);
void test__pointer_usage__less(void** state);
void test__pointer_usage__duplicate(void** state);
/*
 * test range_t usage
 */
UT_CASE_DECLARATION(range_usage)
void test__range_usage__create(void** state);
void test__range_usage__init_n(void** state);
void test__range_usage__init_elem(void** state);
void test__range_usage__iterator(void** state);
void test__range_usage__at(void** state);
void test__range_usage__copy(void** state);
void test__range_usage__less(void** state);
void test__range_usage__duplicate(void** state);
/*
 * test basic_string_t usage
 */
UT_CASE_DECLARATION(basic_string_usage)
void test__basic_string_usage__create(void** state);
void test__basic_string_usage__init_n(void** state);
void test__basic_string_usage__init_elem(void** state);
void test__basic_string_usage__iterator(void** state);
void test__basic_string_usage__at(void** state);
void test__basic_string_usage__copy(void** state);
void test__basic_string_usage__less(void** state);
void test__basic_string_usage__duplicate(void** state);

#ifndef _MSC_VER
/*
 * test _Bool usage
 */
UT_CASE_DECLARATION(bool_usage)
void test__bool_usage__create(void** state);
void test__bool_usage__init_n(void** state);
void test__bool_usage__init_elem(void** state);
void test__bool_usage__iterator(void** state);
void test__bool_usage__at(void** state);
void test__bool_usage__copy(void** state);
void test__bool_usage__less(void** state);
void test__bool_usage__duplicate(void** state);
/*
 * test long long usage
 */
UT_CASE_DECLARATION(long_long_usage)
void test__long_long_usage__create(void** state);
void test__long_long_usage__init_n(void** state);
void test__long_long_usage__init_elem(void** state);
void test__long_long_usage__iterator(void** state);
void test__long_long_usage__at(void** state);
void test__long_long_usage__copy(void** state);
void test__long_long_usage__less(void** state);
void test__long_long_usage__duplicate(void** state);
/*
 * test unsigned long long usage
 */
UT_CASE_DECLARATION(ulong_long_usage)
void test__ulong_long_usage__create(void** state);
void test__ulong_long_usage__init_n(void** state);
void test__ulong_long_usage__init_elem(void** state);
void test__ulong_long_usage__iterator(void** state);
void test__ulong_long_usage__at(void** state);
void test__ulong_long_usage__copy(void** state);
void test__ulong_long_usage__less(void** state);
void test__ulong_long_usage__duplicate(void** state);
#endif

#define UT_CSTL_TYPES_CASE\
    UT_SUIT_BEGIN(cstl_types, test__all_types__char),\
    UT_CASE(test__all_types__signed_char),\
    UT_CASE(test__all_types__unsigned_char),\
    UT_CASE(test__all_types__short),\
    UT_CASE(test__all_types__signed_short),\
    UT_CASE(test__all_types__short_int),\
    UT_CASE(test__all_types__signed_short_int),\
    UT_CASE(test__all_types__unsigned_short),\
    UT_CASE(test__all_types__unsigned_short_int),\
    UT_CASE(test__all_types__int),\
    UT_CASE(test__all_types__signed),\
    UT_CASE(test__all_types__signed_int),\
    UT_CASE(test__all_types__unsigned),\
    UT_CASE(test__all_types__unsigned_int),\
    UT_CASE(test__all_types__long),\
    UT_CASE(test__all_types__signed_long),\
    UT_CASE(test__all_types__long_int),\
    UT_CASE(test__all_types__signed_long_int),\
    UT_CASE(test__all_types__unsigned_long),\
    UT_CASE(test__all_types__unsigned_long_int),\
    UT_CASE(test__all_types__float),\
    UT_CASE(test__all_types__double),\
    UT_CASE(test__all_types__long_double),\
    UT_CASE(test__all_types__cstr),\
    UT_CASE(test__all_types__pointer),\
    UT_CASE(test__all_types__struct),\
    UT_CASE(test__all_types__enum),\
    UT_CASE(test__all_types__union),\
    UT_CASE(test__all_types__id),\
    UT_CASE(test__all_types__vector),\
    UT_CASE(test__all_types__list),\
    UT_CASE(test__all_types__slist),\
    UT_CASE(test__all_types__deque),\
    UT_CASE(test__all_types__queue),\
    UT_CASE(test__all_types__stack),\
    UT_CASE(test__all_types__priority_queue),\
    UT_CASE(test__all_types__set),\
    UT_CASE(test__all_types__multiset),\
    UT_CASE(test__all_types__hash_set),\
    UT_CASE(test__all_types__hash_multiset),\
    UT_CASE(test__all_types__map),\
    UT_CASE(test__all_types__multimap),\
    UT_CASE(test__all_types__hash_map),\
    UT_CASE(test__all_types__hash_multimap),\
    UT_CASE(test__all_types__pair),\
    UT_CASE(test__all_types__string),\
    UT_CASE(test__all_types__cstl_bool),\
    UT_CASE(test__all_types__range),\
    UT_CASE(test__all_types__basic_string),\
    UT_CASE(test__all_types__iterator),\
    UT_CASE(test__all_types__vector_iterator),\
    UT_CASE(test__all_types__list_iterator),\
    UT_CASE(test__all_types__slist_iterator),\
    UT_CASE(test__all_types__deque_iterator),\
    UT_CASE(test__all_types__set_iterator),\
    UT_CASE(test__all_types__map_iterator),\
    UT_CASE(test__all_types__multiset_iterator),\
    UT_CASE(test__all_types__multimap_iterator),\
    UT_CASE(test__all_types__hash_set_iterator),\
    UT_CASE(test__all_types__hash_map_iterator),\
    UT_CASE(test__all_types__hash_multiset_iterator),\
    UT_CASE(test__all_types__hash_multimap_iterator),\
    UT_CASE(test__all_types__string_iterator),\
    UT_CASE(test__all_types__input_iterator),\
    UT_CASE(test__all_types__output_iterator),\
    UT_CASE(test__all_types__forward_iterator),\
    UT_CASE(test__all_types__bidirectional_iterator),\
    UT_CASE(test__all_types__random_access_iterator),\
    UT_CASE(test__all_types__basic_string_iterator),\
    UT_CASE_BEGIN(_type_init_default, test__type_init_default__null_input),\
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
    UT_CASE_BEGIN(pointer_usage, test__pointer_usage__create),\
    UT_CASE(test__pointer_usage__init_n),\
    UT_CASE(test__pointer_usage__init_elem),\
    UT_CASE(test__pointer_usage__at),\
    UT_CASE(test__pointer_usage__iterator),\
    UT_CASE(test__pointer_usage__copy),\
    UT_CASE(test__pointer_usage__less),\
    UT_CASE(test__pointer_usage__duplicate),\
    UT_CASE_BEGIN(range_usage, test__range_usage__create),\
    UT_CASE(test__range_usage__init_n),\
    UT_CASE(test__range_usage__init_elem),\
    UT_CASE(test__range_usage__at),\
    UT_CASE(test__range_usage__iterator),\
    UT_CASE(test__range_usage__copy),\
    UT_CASE(test__range_usage__less),\
    UT_CASE(test__range_usage__duplicate),\
    UT_CASE_BEGIN(basic_string_usage, test__basic_string_usage__create),\
    UT_CASE(test__basic_string_usage__init_n),\
    UT_CASE(test__basic_string_usage__init_elem),\
    UT_CASE(test__basic_string_usage__at),\
    UT_CASE(test__basic_string_usage__iterator),\
    UT_CASE(test__basic_string_usage__copy),\
    UT_CASE(test__basic_string_usage__less),\
    UT_CASE(test__basic_string_usage__duplicate)

#ifndef _MSC_VER
#define UT_CSTL_TYPES_CASE_C99\
    UT_SUIT_BEGIN(cstl_types, test__all_types__bool),\
    UT_CASE(test__all_types__long_long),\
    UT_CASE(test__all_types__long_long_int),\
    UT_CASE(test__all_types__signed_long_long),\
    UT_CASE(test__all_types__signed_long_long_int),\
    UT_CASE(test__all_types__unsigned_long_long),\
    UT_CASE(test__all_types__unsigned_long_long_int),\
    UT_CASE_BEGIN(bool_usage, test__bool_usage__create),\
    UT_CASE(test__bool_usage__init_n),\
    UT_CASE(test__bool_usage__init_elem),\
    UT_CASE(test__bool_usage__at),\
    UT_CASE(test__bool_usage__iterator),\
    UT_CASE(test__bool_usage__copy),\
    UT_CASE(test__bool_usage__less),\
    UT_CASE(test__bool_usage__duplicate),\
    UT_CASE_BEGIN(long_long_usage, test__long_long_usage__create),\
    UT_CASE(test__long_long_usage__init_n),\
    UT_CASE(test__long_long_usage__init_elem),\
    UT_CASE(test__long_long_usage__at),\
    UT_CASE(test__long_long_usage__iterator),\
    UT_CASE(test__long_long_usage__copy),\
    UT_CASE(test__long_long_usage__less),\
    UT_CASE(test__long_long_usage__duplicate),\
    UT_CASE_BEGIN(ulong_long_usage, test__ulong_long_usage__create),\
    UT_CASE(test__ulong_long_usage__init_n),\
    UT_CASE(test__ulong_long_usage__init_elem),\
    UT_CASE(test__ulong_long_usage__at),\
    UT_CASE(test__ulong_long_usage__iterator),\
    UT_CASE(test__ulong_long_usage__copy),\
    UT_CASE(test__ulong_long_usage__less),\
    UT_CASE(test__ulong_long_usage__duplicate)
#endif

#endif /* _UT_CSTL_TYPES_H_ */

