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
/*
 * test _algo_replace_if and _algo_replace_if_varg
 */
UT_CASE_DECLARATION(_algo_replace_if__algo_replace_if_varg)
void test__algo_replace_if__algo_replace_if_varg__invalid_range(void** state);
void test__algo_replace_if__algo_replace_if_varg__invalid_range2(void** state);
void test__algo_replace_if__algo_replace_if_varg__invalid_range3(void** state);
void test__algo_replace_if__algo_replace_if_varg__range_empty(void** state);
void test__algo_replace_if__algo_replace_if_varg__ufun_NULL(void** state);
void test__algo_replace_if__algo_replace_if_varg__c_builtin(void** state);
void test__algo_replace_if__algo_replace_if_varg__cstr(void** state);
void test__algo_replace_if__algo_replace_if_varg__cstl_builtin(void** state);
void test__algo_replace_if__algo_replace_if_varg__user_define(void** state);
/*
 * test _algo_replace_copy_if and _algo_replace_copy_if_varg
 */
UT_CASE_DECLARATION(_algo_replace_copy_if__algo_replace_copy_if_varg)
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range2(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range3(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_dest_range(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_range_not_same_type(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__bfun_op_NULL(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__c_builtin(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__cstr(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__cstl_builtin(void** state);
void test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define(void** state);
/*
 * test _algo_fill and _algo_fill_varg
 */
UT_CASE_DECLARATION(_algo_fill__algo_fill_varg)
void test__algo_fill__algo_fill_varg__invalid_range(void** state);
void test__algo_fill__algo_fill_varg__invalid_range2(void** state);
void test__algo_fill__algo_fill_varg__invalid_range3(void** state);
void test__algo_fill__algo_fill_varg__empty(void** state);
void test__algo_fill__algo_fill_varg__c_builtin(void** state);
void test__algo_fill__algo_fill_varg__cstr(void** state);
void test__algo_fill__algo_fill_varg__cstl_builtin(void** state);
void test__algo_fill__algo_fill_varg__user_define(void** state);
/*
 * test _algo_fill_n and _algo_fill_n_varg
 */
UT_CASE_DECLARATION(_algo_fill_n__algo_fill_n_varg)
void test__algo_fill_n__algo_fill_n_varg__invalid_range(void** state);
void test__algo_fill_n__algo_fill_n_varg__empty(void** state);
void test__algo_fill_n__algo_fill_n_varg__c_builtin(void** state);
void test__algo_fill_n__algo_fill_n_varg__cstr(void** state);
void test__algo_fill_n__algo_fill_n_varg__cstl_builtin(void** state);
void test__algo_fill_n__algo_fill_n_varg__user_define(void** state);
/*
 * test _algo_remove and _algo_remove_varg
 */
UT_CASE_DECLARATION(_algo_remove__algo_remove_varg)
void test__algo_remove__algo_remove_varg__invalid_range(void** state);
void test__algo_remove__algo_remove_varg__invalid_range2(void** state);
void test__algo_remove__algo_remove_varg__invalid_range3(void** state);
void test__algo_remove__algo_remove_varg__empty(void** state);
void test__algo_remove__algo_remove_varg__c_builtin(void** state);
void test__algo_remove__algo_remove_varg__cstr(void** state);
void test__algo_remove__algo_remove_varg__cstl_builtin(void** state);
void test__algo_remove__algo_remove_varg__user_define(void** state);
/*
 * test _algo_remove_copy and _algo_remove_copy_varg
 */
UT_CASE_DECLARATION(_algo_remove_copy__algo_remove_copy_varg)
void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range2(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range3(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__invalid_dest_range(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__invalid_range_not_same_type(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__source_range_empty(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__c_builtin(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__cstr(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__cstl_builtin(void** state);
void test__algo_remove_copy__algo_remove_copy_varg__user_define(void** state);

#define UT_CSTL_ALGO_MUTATING_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_algo_mutating_private, test__algo_replace_once__algo_replace_once_varg__invalid_iter),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__c_builtin),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__cstr),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__cstl_builtin),\
    UT_CASE(test__algo_replace_once__algo_replace_once_varg__user_define),\
    UT_CASE_BEGIN(_algo_replace_if__algo_replace_if_varg, test__algo_replace_if__algo_replace_if_varg__invalid_range),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__invalid_range2),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__invalid_range3),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__range_empty),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__ufun_NULL),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__c_builtin),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__cstr),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__cstl_builtin),\
    UT_CASE(test__algo_replace_if__algo_replace_if_varg__user_define),\
    UT_CASE_BEGIN(_algo_replace_copy_if__algo_replace_copy_if_varg, test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range2),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_source_range3),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_dest_range),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__invalid_range_not_same_type),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__bfun_op_NULL),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__c_builtin),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__cstr),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__cstl_builtin),\
    UT_CASE(test__algo_replace_copy_if__algo_replace_copy_if_varg__user_define),\
    UT_CASE_BEGIN(_algo_fill__algo_fill_varg, test__algo_fill__algo_fill_varg__invalid_range),\
    UT_CASE(test__algo_fill__algo_fill_varg__invalid_range2),\
    UT_CASE(test__algo_fill__algo_fill_varg__invalid_range3),\
    UT_CASE(test__algo_fill__algo_fill_varg__empty),\
    UT_CASE(test__algo_fill__algo_fill_varg__c_builtin),\
    UT_CASE(test__algo_fill__algo_fill_varg__cstr),\
    UT_CASE(test__algo_fill__algo_fill_varg__cstl_builtin),\
    UT_CASE(test__algo_fill__algo_fill_varg__user_define),\
    UT_CASE_BEGIN(_algo_fill_n__algo_fill_n_varg, test__algo_fill_n__algo_fill_n_varg__invalid_range),\
    UT_CASE(test__algo_fill_n__algo_fill_n_varg__empty),\
    UT_CASE(test__algo_fill_n__algo_fill_n_varg__c_builtin),\
    UT_CASE(test__algo_fill_n__algo_fill_n_varg__cstr),\
    UT_CASE(test__algo_fill_n__algo_fill_n_varg__cstl_builtin),\
    UT_CASE(test__algo_fill_n__algo_fill_n_varg__user_define),\
    UT_CASE_BEGIN(_algo_remove__algo_remove_varg, test__algo_remove__algo_remove_varg__invalid_range),\
    UT_CASE(test__algo_remove__algo_remove_varg__invalid_range2),\
    UT_CASE(test__algo_remove__algo_remove_varg__invalid_range3),\
    UT_CASE(test__algo_remove__algo_remove_varg__empty),\
    UT_CASE(test__algo_remove__algo_remove_varg__c_builtin),\
    UT_CASE(test__algo_remove__algo_remove_varg__cstr),\
    UT_CASE(test__algo_remove__algo_remove_varg__cstl_builtin),\
    UT_CASE(test__algo_remove__algo_remove_varg__user_define),\
    UT_CASE_BEGIN(_algo_remove_copy__algo_remove_copy_varg, test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range2),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__invalid_source_range3),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__invalid_dest_range),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__invalid_range_not_same_type),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__source_range_empty),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__c_builtin),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__cstr),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__cstl_builtin),\
    UT_CASE(test__algo_remove_copy__algo_remove_copy_varg__user_define)

#endif /* _UT_CSTL_ALGO_MUTATING_PRIVATE_H_ */

