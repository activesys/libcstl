#ifndef _UT_CSTL_ALGO_NONMUTATING_PRIVATE_H_
#define _UT_CSTL_ALGO_NONMUTATING_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_algo_nonmutating_private)
/*
 * test _algo_find and _algo_find_varg
 */
UT_CASE_DECLARATION(_algo_find__algo_find_varg)
void test__algo_find__algo_find_varg__invalid_range(void** state);
void test__algo_find__algo_find_varg__invalid_range_2(void** state);
void test__algo_find__algo_find_varg__empty(void** state);
void test__algo_find__algo_find_varg__c_builtin_not_found(void** state);
void test__algo_find__algo_find_varg__c_builtin_found(void** state);
void test__algo_find__algo_find_varg__cstr_not_found(void** state);
void test__algo_find__algo_find_varg__cstr_found(void** state);
void test__algo_find__algo_find_varg__cstl_builtin_not_found(void** state);
void test__algo_find__algo_find_varg__cstl_builtin_found(void** state);
void test__algo_find__algo_find_varg__user_define_not_found(void** state);
void test__algo_find__algo_find_varg__user_define_found(void** state);

#define UT_CSTL_ALGO_NONMUTATING_PRIVATE_CASE\
	UT_SUIT_BEGIN(cstl_algo_nonmutating_private, test__algo_find__algo_find_varg__invalid_range),\
    UT_CASE(test__algo_find__algo_find_varg__invalid_range_2),\
    UT_CASE(test__algo_find__algo_find_varg__empty),\
    UT_CASE(test__algo_find__algo_find_varg__c_builtin_not_found),\
    UT_CASE(test__algo_find__algo_find_varg__c_builtin_found),\
    UT_CASE(test__algo_find__algo_find_varg__cstr_not_found),\
    UT_CASE(test__algo_find__algo_find_varg__cstr_found),\
    UT_CASE(test__algo_find__algo_find_varg__cstl_builtin_not_found),\
    UT_CASE(test__algo_find__algo_find_varg__cstl_builtin_found),\
    UT_CASE(test__algo_find__algo_find_varg__user_define_not_found),\
    UT_CASE(test__algo_find__algo_find_varg__user_define_found)

#endif /* _UT_CSTL_ALGO_NONMUTATING_PRIVATE_H_ */

