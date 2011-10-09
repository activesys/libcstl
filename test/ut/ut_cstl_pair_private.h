#ifndef _UT_CSTL_PAIR_PRIVATE_H_
#define _UT_CSTL_PAIR_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_pair_private)
/*
 * test _pair_is_created
 */
UT_CASE_DECLARATION(_pair_is_created)
void test__pair_is_created__null_pair(void** state);
void test__pair_is_created__invalid_first(void** state);
void test__pair_is_created__invalid_second(void** state);
void test__pair_is_created__invalid_mapkeycompare(void** state);
void test__pair_is_created__invalid_mapvaluecompare(void** state);
void test__pair_is_created__invalid_typeinfofirst_style(void** state);
void test__pair_is_created__invalid_typeinfofirst_type(void** state);
void test__pair_is_created__invalid_typeinfosecond_style(void** state);
void test__pair_is_created__invalid_typeinfosecond_type(void** state);
void test__pair_is_created__created(void** state);
/*
 * test _pair_is_inited
 */
UT_CASE_DECLARATION(_pair_is_inited)
void test__pair_is_inited__null_pair(void** state);
void test__pair_is_inited__null_pair_first(void** state);
void test__pair_is_inited__null_pair_second(void** state);
void test__pair_is_inited__invalid_typeinfofirst_style(void** state);
void test__pair_is_inited__invalid_typeinfofirst_type(void** state);
void test__pair_is_inited__invalid_typeinfosecond_style(void** state);
void test__pair_is_inited__invalid_typeinfosecond_type(void** state);
/*
 * test _create_pair
 */
UT_CASE_DECLARATION(_create_pair)
void test__create_pair__null_typename(void** state);
void test__create_pair__c_builtin(void** state);
void test__create_pair__cstr(void** state);
void test__create_pair__libcstl_builtin(void** state);
void test__create_pair__user_define(void** state);
void test__create_pair__unregister(void** state);
void test__create_pair__invalid(void** state);
/*
 * test _create_pair_auxiliary
 */
UT_CASE_DECLARATION(_create_pair_auxiliary)
void test__create_pair_auxiliary__null_pair(void** state);
void test__create_pair_auxiliary__null_typename(void** state);
void test__create_pair_auxiliary__unregistered(void** state);
void test__create_pair_auxiliary__c_builtin(void** state);
void test__create_pair_auxiliary__cstr(void** state);
void test__create_pair_auxiliary__libcstl_builtin(void** state);
void test__create_pair_auxiliary__user_define(void** state);
/*
 * test _pair_destroy_auxiliary
 */
UT_CASE_DECLARATION(_pair_destroy_auxiliary)
void test__pair_destroy_auxiliary__null_pair(void** state);
void test__pair_destroy_auxiliary__non_created(void** state);
void test__pair_destroy_auxiliary__non_inited(void** state);
void test__pair_destroy_auxiliary__empty(void** state);
void test__pair_destroy_auxiliary__non_empty(void** state);
void test__pair_destroy_auxiliary__created_not_inited(void** state);
/*
 * test _pair_make_first
 */
UT_CASE_DECLARATION(_pair_make_first)
void test__pair_make_first__null_pair(void** state);
void test__pair_make_first__non_inited(void** state);
void test__pair_make_first__c_builtin(void** state);
void test__pair_make_first__str(void** state);
void test__pair_make_first__libcstl_builtin(void** state);
void test__pair_make_first__user_define(void** state);
/*
 * test _pair_make_second
 */
UT_CASE_DECLARATION(_pair_make_second)
void test__pair_make_second__null_pair(void** state);
void test__pair_make_second__non_inited(void** state);
void test__pair_make_second__c_builtin(void** state);
void test__pair_make_second__str(void** state);
void test__pair_make_second__libcstl_builtin(void** state);
void test__pair_make_second__user_define(void** state);

#define UT_CSTL_PAIR_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_pair_private, test__pair_is_created__null_pair),\
    UT_CASE(test__pair_is_created__invalid_first),\
    UT_CASE(test__pair_is_created__invalid_second),\
    UT_CASE(test__pair_is_created__invalid_mapkeycompare),\
    UT_CASE(test__pair_is_created__invalid_mapvaluecompare),\
    UT_CASE(test__pair_is_created__invalid_typeinfofirst_style),\
    UT_CASE(test__pair_is_created__invalid_typeinfofirst_type),\
    UT_CASE(test__pair_is_created__invalid_typeinfosecond_style),\
    UT_CASE(test__pair_is_created__invalid_typeinfosecond_type),\
    UT_CASE(test__pair_is_created__created),\
    UT_CASE_BEGIN(_pair_is_inited, test__pair_is_inited__null_pair),\
    UT_CASE(test__pair_is_inited__null_pair_first),\
    UT_CASE(test__pair_is_inited__null_pair_second),\
    UT_CASE(test__pair_is_inited__invalid_typeinfofirst_style),\
    UT_CASE(test__pair_is_inited__invalid_typeinfofirst_type),\
    UT_CASE(test__pair_is_inited__invalid_typeinfosecond_style),\
    UT_CASE(test__pair_is_inited__invalid_typeinfosecond_type),\
    UT_SUIT_BEGIN(cstl_pair_private, test__create_pair__null_typename),\
    UT_CASE(test__create_pair__c_builtin),\
    UT_CASE(test__create_pair__cstr),\
    UT_CASE(test__create_pair__libcstl_builtin),\
    UT_CASE(test__create_pair__user_define),\
    UT_CASE(test__create_pair__unregister),\
    UT_CASE(test__create_pair__invalid),\
    UT_CASE_BEGIN(_create_pair_auxiliary, test__create_pair_auxiliary__null_pair),\
    UT_CASE(test__create_pair_auxiliary__null_typename),\
    UT_CASE(test__create_pair_auxiliary__unregistered),\
    UT_CASE(test__create_pair_auxiliary__c_builtin),\
    UT_CASE(test__create_pair_auxiliary__cstr),\
    UT_CASE(test__create_pair_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_pair_auxiliary__user_define),\
    UT_CASE_BEGIN(_pair_destroy_auxiliary, test__pair_destroy_auxiliary__null_pair),\
    UT_CASE(test__pair_destroy_auxiliary__non_created),\
    UT_CASE(test__pair_destroy_auxiliary__non_inited),\
    UT_CASE(test__pair_destroy_auxiliary__empty),\
    UT_CASE(test__pair_destroy_auxiliary__non_empty),\
    UT_CASE(test__pair_destroy_auxiliary__created_not_inited),\
    UT_CASE_BEGIN(_pair_make_first, test__pair_make_first__null_pair),\
    UT_CASE(test__pair_make_first__non_inited),\
    UT_CASE(test__pair_make_first__c_builtin),\
    UT_CASE(test__pair_make_first__str),\
    UT_CASE(test__pair_make_first__libcstl_builtin),\
    UT_CASE(test__pair_make_first__user_define),\
    UT_CASE_BEGIN(_pair_make_second, test__pair_make_second__null_pair),\
    UT_CASE(test__pair_make_second__non_inited),\
    UT_CASE(test__pair_make_second__c_builtin),\
    UT_CASE(test__pair_make_second__str),\
    UT_CASE(test__pair_make_second__libcstl_builtin),\
    UT_CASE(test__pair_make_second__user_define)

#endif /* _UT_CSTL_PAIR_PRIVATE_H_ */

