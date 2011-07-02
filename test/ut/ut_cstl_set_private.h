#ifndef _UT_CSTL_SET_PRIVATE_H_
#define _UT_CSTL_SET_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_set_private)
/*
 * test _create_set
 */
UT_CASE_DECLARATION(_create_set)
void test__create_set__null_typename(void** state);
void test__create_set__c_builtin(void** state);
void test__create_set__cstr(void** state);
void test__create_set__libcstl_builtin(void** state);
void test__create_set__user_define(void** state);
void test__create_set__unregister(void** state);
/*
 * test _create_set_auxiliary
 */
UT_CASE_DECLARATION(_create_set_auxiliary)
void test__create_set_auxiliary__null_set(void** state);
void test__create_set_auxiliary__null_typename(void** state);
void test__create_set_auxiliary__unregistered(void** state);
void test__create_set_auxiliary__c_builtin(void** state);
void test__create_set_auxiliary__cstr(void** state);
void test__create_set_auxiliary__libcstl_builtin(void** state);
void test__create_set_auxiliary__user_define(void** state);
/*
 * test _set_destroy_auxiliary
 */
UT_CASE_DECLARATION(_set_destroy_auxiliary)
void test__set_destroy_auxiliary__null_set(void** state);
void test__set_destroy_auxiliary__non_created(void** state);
void test__set_destroy_auxiliary__non_inited(void** state);
void test__set_destroy_auxiliary__empty(void** state);
void test__set_destroy_auxiliary__non_empty(void** state);

#define UT_CSTL_SET_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_set_private, test__create_set__null_typename),\
    UT_CASE(test__create_set__c_builtin),\
    UT_CASE(test__create_set__cstr),\
    UT_CASE(test__create_set__libcstl_builtin),\
    UT_CASE(test__create_set__user_define),\
    UT_CASE(test__create_set__unregister),\
    UT_CASE_BEGIN(_create_set_auxiliary, test__create_set_auxiliary__null_set),\
    UT_CASE(test__create_set_auxiliary__null_typename),\
    UT_CASE(test__create_set_auxiliary__unregistered),\
    UT_CASE(test__create_set_auxiliary__c_builtin),\
    UT_CASE(test__create_set_auxiliary__cstr),\
    UT_CASE(test__create_set_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_set_auxiliary__user_define),\
    UT_CASE_BEGIN(_set_destroy_auxiliary, test__set_destroy_auxiliary__null_set),\
    UT_CASE(test__set_destroy_auxiliary__non_created),\
    UT_CASE(test__set_destroy_auxiliary__non_inited),\
    UT_CASE(test__set_destroy_auxiliary__empty),\
    UT_CASE(test__set_destroy_auxiliary__non_empty),\

#endif /* _UT_CSTL_SET_PRIVATE_H_ */

