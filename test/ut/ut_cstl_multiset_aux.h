#ifndef _UT_CSTL_MULTISET_AUX_H_
#define _UT_CSTL_MULTISET_AUX_H_

UT_SUIT_DECLARATION(cstl_multiset_aux)

/*
 * test _multiset_get_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_multiset_get_varg_value_auxiliary)
void test__multiset_get_varg_value_auxiliary__null_multiset_container(void** state);
void test__multiset_get_varg_value_auxiliary__null_node(void** state);
/*void test__multiset_get_varg_value_auxiliary__non_created_multiset_containter(void** state);*/
void test__multiset_get_varg_value_auxiliary__c_builtin(void** state);
void test__multiset_get_varg_value_auxiliary__cstr(void** state);
void test__multiset_get_varg_value_auxiliary__libcstl_builtin(void** state);
void test__multiset_get_varg_value_auxiliary__user_define(void** state);
/*
 * test _multiset_destroy_varg_value_auxiliary
 */
UT_CASE_DECLARATION(_multiset_destroy_varg_value_auxiliary)
void test__multiset_destroy_varg_value_auxiliary__null_multiset_container(void** state);
void test__multiset_destroy_varg_value_auxiliary__null_varg(void** state);
/*void test__multiset_destroy_varg_value_auxiliary__non_created(void** state);*/
void test__multiset_destroy_varg_value_auxiliary__successfully(void** state);

#define UT_CSTL_MULTISET_AUX_CASE\
    UT_SUIT_BEGIN(cstl_multiset_aux, test__multiset_get_varg_value_auxiliary__null_multiset_container),\
    UT_CASE(test__multiset_get_varg_value_auxiliary__null_node),\
    UT_CASE(test__multiset_get_varg_value_auxiliary__c_builtin),\
    UT_CASE(test__multiset_get_varg_value_auxiliary__cstr),\
    UT_CASE(test__multiset_get_varg_value_auxiliary__libcstl_builtin),\
    UT_CASE(test__multiset_get_varg_value_auxiliary__user_define),\
    UT_CASE_BEGIN(_multiset_destroy_varg_value_auxiliary, test__multiset_destroy_varg_value_auxiliary__null_multiset_container),\
    UT_CASE(test__multiset_destroy_varg_value_auxiliary__null_varg),\
    UT_CASE(test__multiset_destroy_varg_value_auxiliary__successfully)

#endif /* _UT_CSTL_MULTISET_AUX_H_ */

