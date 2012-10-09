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
/*
 * test _algo_count and _algo_count_varg
 */
UT_CASE_DECLARATION(_algo_count__algo_count_varg)
void test__algo_count__algo_count_varg__invalid_range(void** state);
void test__algo_count__algo_count_varg__invalid_range2(void** state);
void test__algo_count__algo_count_varg__empty(void** state);
void test__algo_count__algo_count_varg__c_builtin_0(void** state);
void test__algo_count__algo_count_varg__c_builtin_1(void** state);
void test__algo_count__algo_count_varg__c_builtin_n(void** state);
void test__algo_count__algo_count_varg__cstr_0(void** state);
void test__algo_count__algo_count_varg__cstr_1(void** state);
void test__algo_count__algo_count_varg__cstr_n(void** state);
void test__algo_count__algo_count_varg__cstl_builtin_0(void** state);
void test__algo_count__algo_count_varg__cstl_builtin_1(void** state);
void test__algo_count__algo_count_varg__cstl_builtin_n(void** state);
void test__algo_count__algo_count_varg__user_define_0(void** state);
void test__algo_count__algo_count_varg__user_define_1(void** state);
void test__algo_count__algo_count_varg__user_define_n(void** state);

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
    UT_CASE(test__algo_find__algo_find_varg__user_define_found),\
    UT_CASE_BEGIN(_algo_count__algo_count_varg, test__algo_count__algo_count_varg__invalid_range),\
    UT_CASE(test__algo_count__algo_count_varg__invalid_range2),\
    UT_CASE(test__algo_count__algo_count_varg__empty),\
    UT_CASE(test__algo_count__algo_count_varg__c_builtin_0),\
    UT_CASE(test__algo_count__algo_count_varg__c_builtin_1),\
    UT_CASE(test__algo_count__algo_count_varg__c_builtin_n),\
    UT_CASE(test__algo_count__algo_count_varg__cstr_0),\
    UT_CASE(test__algo_count__algo_count_varg__cstr_1),\
    UT_CASE(test__algo_count__algo_count_varg__cstr_n),\
    UT_CASE(test__algo_count__algo_count_varg__cstl_builtin_0),\
    UT_CASE(test__algo_count__algo_count_varg__cstl_builtin_1),\
    UT_CASE(test__algo_count__algo_count_varg__cstl_builtin_n),\
    UT_CASE(test__algo_count__algo_count_varg__user_define_0),\
    UT_CASE(test__algo_count__algo_count_varg__user_define_1),\
    UT_CASE(test__algo_count__algo_count_varg__user_define_n)

#endif /* _UT_CSTL_ALGO_NONMUTATING_PRIVATE_H_ */

