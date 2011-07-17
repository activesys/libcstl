#ifndef _UT_CSTL_MULTISET_PRIVATE_H_
#define _UT_CSTL_MULTISET_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_multiset_private)
/*
 * test _create_multiset
 */
UT_CASE_DECLARATION(_create_multiset)
void test__create_multiset__null_typename(void** state);
void test__create_multiset__c_builtin(void** state);
void test__create_multiset__cstr(void** state);
void test__create_multiset__libcstl_builtin(void** state);
void test__create_multiset__user_define(void** state);
void test__create_multiset__unregister(void** state);

#define UT_CSTL_MULTISET_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_multiset_private, test__create_multiset__null_typename),\
    UT_CASE(test__create_multiset__c_builtin),\
    UT_CASE(test__create_multiset__cstr),\
    UT_CASE(test__create_multiset__libcstl_builtin),\
    UT_CASE(test__create_multiset__user_define),\
    UT_CASE(test__create_multiset__unregister),\

#endif /* _UT_CSTL_MULTISET_PRIVATE_H_ */

