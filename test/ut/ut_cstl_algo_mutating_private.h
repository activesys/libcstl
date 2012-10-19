#ifndef _UT_CSTL_ALGO_MUTATING_PRIVATE_H_
#define _UT_CSTL_ALGO_MUTATING_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_algo_mutating_private)

/*
 * test _algo_replace_once and _algo_replace_once_varg
 */
UT_CASE_DECLARATION(_algo_replace_once__algo_replace_once_varg)
void test__algo_replace_once__algo_replace_once_varg__invalid_iter(void** state);
void test__algo_replace_once__algo_replace_once_varg__c_builtin(void** state);
void test__algo_replace_once__algo_replace_once_varg__cstr(void** state);
void test__algo_replace_once__algo_replace_once_varg__cstl_builtin(void** state);
void test__algo_replace_once__algo_replace_once_varg__user_define(void** state);

#define UT_CSTL_ALGO_MUTATING_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_algo_mutating_private, test__algo_replace_once__algo_replace_once_varg__invalid_iter),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__c_builtin),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__cstr),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__cstl_builtin),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__user_define)

#endif /* _UT_CSTL_ALGO_MUTATING_PRIVATE_H_ */

