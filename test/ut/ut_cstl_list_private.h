#ifndef _UT_CSTL_LIST_PRIVATE_H_
#define _UT_CSTL_LIST_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_list_private)

/*
 * test _create_list
 */
UT_CASE_DECLARATION(_create_list)
void test__create_list__null_typename(void** state);
void test__create_list__unregisted_type(void** state);
void test__create_list__c_builtin_type(void** state);
void test__create_list__libcstl_builtin_type(void** state);
void test__create_list__user_defined_type(void** state);
void test__create_list__user_defined_type_dup(void** state);

#define UT_CSTL_LIST_PRIVATE_CASE \
    UT_SUIT_BEGIN(cstl_list_private, test__create_list__null_typename),\
    UT_CASE(test__create_list__unregisted_type),\
    UT_CASE(test__create_list__c_builtin_type),\
    UT_CASE(test__create_list__libcstl_builtin_type),\
    UT_CASE(test__create_list__user_defined_type),\
    UT_CASE(test__create_list__user_defined_type_dup)

#endif /* _UT_CSTL_LIST_PRIVATE_H_ */
