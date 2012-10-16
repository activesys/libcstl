#ifndef _UT_CSTL_ALGO_NONMUTATING_H_
#define _UT_CSTL_ALGO_NONMUTATING_H_

UT_SUIT_DECLARATION(cstl_algo_nonmutating)
/*
 * test algo_for_each
 */
UT_CASE_DECLARATION(algo_for_each)
void test_algo_for_each__invalid_range(void** state);
void test_algo_for_each__invalid_range_2(void** state);
void test_algo_for_each__empty_range(void** state);
void test_algo_for_each__ufun_NULL(void** state);
void test_algo_for_each__mutate_all(void** state);
void test_algo_for_each__mutate_partial(void** state);
void test_algo_for_each__cstr(void** state);
void test_algo_for_each__cstl_builtin(void** state);
void test_algo_for_each__user_define(void** state);
/*
 * test algo_find_if
 */
UT_CASE_DECLARATION(algo_find_if)
void test_algo_find_if__invalid_range(void** state);
void test_algo_find_if__invalid_range_2(void** state);
void test_algo_find_if__empty_range(void** state);
void test_algo_find_if__ufun_NULL(void** state);
void test_algo_find_if__c_builtin_found(void** state);
void test_algo_find_if__c_builtin_not_found(void** state);
void test_algo_find_if__cstr_found(void** state);
void test_algo_find_if__cstr_not_found(void** state);
void test_algo_find_if__cstl_builtin_found(void** state);
void test_algo_find_if__cstl_builtin_not_found(void** state);
void test_algo_find_if__user_define_found(void** state);
void test_algo_find_if__user_define_not_found(void** state);
/*
 * test algo_adjacent_find
 */
UT_CASE_DECLARATION(algo_adjacent_find)
void test_algo_adjacent_find__invalid_range_invalid_iter(void** state);
void test_algo_adjacent_find__invalid_range_not_belong_to_same_container(void** state);
void test_algo_adjacent_find__invalid_range_reverse(void** state);
void test_algo_adjacent_find__c_builtin_found(void** state);
void test_algo_adjacent_find__c_builtin_not_found(void** state);
void test_algo_adjacent_find__cstr_found(void** state);
void test_algo_adjacent_find__cstr_not_found(void** state);
void test_algo_adjacent_find__cstl_builtin_found(void** state);
void test_algo_adjacent_find__cstl_builtin_not_found(void** state);
void test_algo_adjacent_find__user_define_found(void** state);
void test_algo_adjacent_find__user_define_not_found(void** state);
void test_algo_adjacent_find__empty(void** state);
/*
 * test algo_adjacent_find_if
 */
UT_CASE_DECLARATION(algo_adjacent_find_if)
void test_algo_adjacent_find_if__invalid_range_invalid_iter(void** state);
void test_algo_adjacent_find_if__invalid_range_not_belong_to_same_container(void** state);
void test_algo_adjacent_find_if__invalid_range_reverse(void** state);
void test_algo_adjacent_find_if__empty(void** state);
void test_algo_adjacent_find_if__bfun_NULL_found(void** state);
void test_algo_adjacent_find_if__bfun_NULL_not_found(void** state);
void test_algo_adjacent_find_if__c_builtin_found(void** state);
void test_algo_adjacent_find_if__c_builtin_not_found(void** state);
void test_algo_adjacent_find_if__cstr_found(void** state);
void test_algo_adjacent_find_if__cstr_not_found(void** state);
void test_algo_adjacent_find_if__cstl_builtin_found(void** state);
void test_algo_adjacent_find_if__cstl_builtin_not_found(void** state);
void test_algo_adjacent_find_if__user_define_found(void** state);
void test_algo_adjacent_find_if__user_define_not_found(void** state);
/*
 * test algo_find_first_of
 */
UT_CASE_DECLARATION(algo_find_first_of)
void test_algo_find_first_of__invalid_first_range_not_belong_to_same(void** state);
void test_algo_find_first_of__invalid_first_range_reverse(void** state);
void test_algo_find_first_of__invalid_second_range_invalid_iter(void** state);
void test_algo_find_first_of__invalid_second_range_not_belong_to_same(void** state);
void test_algo_find_first_of__invalid_second_range_reverse(void** state);
void test_algo_find_first_of__first_range_empty(void** state);
void test_algo_find_first_of__second_range_empty(void** state);
void test_algo_find_first_of__c_builtin_found(void** state);
void test_algo_find_first_of__c_builtin_not_found(void** state);
void test_algo_find_first_of__cstr_found(void** state);
void test_algo_find_first_of__cstr_not_found(void** state);
void test_algo_find_first_of__cstl_builtin_found(void** state);
void test_algo_find_first_of__cstl_builtin_not_found(void** state);
void test_algo_find_first_of__user_define_found(void** state);
void test_algo_find_first_of__user_define_not_found(void** state);
/*
 * test algo_find_first_of_if
 */
UT_CASE_DECLARATION(algo_find_first_of_if)
void test_algo_find_first_of_if__invalid_first_range_not_belong_to_same(void** state);
void test_algo_find_first_of_if__invalid_first_range_reverse(void** state);
void test_algo_find_first_of_if__invalid_second_range_invalid_iter(void** state);
void test_algo_find_first_of_if__invalid_second_range_not_belong_to_same(void** state);
void test_algo_find_first_of_if__invalid_second_range_reverse(void** state);
void test_algo_find_first_of_if__first_range_empty(void** state);
void test_algo_find_first_of_if__second_range_empty(void** state);
void test_algo_find_first_of_if__bfun_NULL_found(void** state);
void test_algo_find_first_of_if__bfun_NULL_not_found(void** state);
void test_algo_find_first_of_if__c_builtin_found(void** state);
void test_algo_find_first_of_if__c_builtin_not_found(void** state);
void test_algo_find_first_of_if__cstr_found(void** state);
void test_algo_find_first_of_if__cstr_not_found(void** state);
void test_algo_find_first_of_if__cstl_builtin_found(void** state);
void test_algo_find_first_of_if__cstl_builtin_not_found(void** state);
void test_algo_find_first_of_if__user_define_found(void** state);
void test_algo_find_first_of_if__user_define_not_found(void** state);
void test_algo_find_first_of_if__not_same_type(void** state);
/*
 * test algo_count_if
 */
UT_CASE_DECLARATION(algo_count_if)
void test_algo_count_if__invalid_range(void** state);
void test_algo_count_if__invalid_range2(void** state);
void test_algo_count_if__empty(void** state);
void test_algo_count_if__ufun_NULL(void** state);
void test_algo_count_if__c_builtin_0(void** state);
void test_algo_count_if__c_builtin_1(void** state);
void test_algo_count_if__c_builtin_n(void** state);
void test_algo_count_if__cstr_0(void** state);
void test_algo_count_if__cstr_1(void** state);
void test_algo_count_if__cstr_n(void** state);
void test_algo_count_if__cstl_builtin_0(void** state);
void test_algo_count_if__cstl_builtin_1(void** state);
void test_algo_count_if__cstl_builtin_n(void** state);
void test_algo_count_if__user_define_0(void** state);
void test_algo_count_if__user_define_1(void** state);
void test_algo_count_if__user_define_n(void** state);
/*
 * test algo_mismatch
 */
UT_CASE_DECLARATION(algo_mismatch)
void test_algo_mismatch__invalid_first_range(void** state);
void test_algo_mismatch__invalid_first_range2(void** state);
void test_algo_mismatch__invalid_range_not_same_type(void** state);
void test_algo_mismatch__first_range_empty(void** state);
void test_algo_mismatch__c_builtin_mismatch(void** state);
void test_algo_mismatch__c_builtin_match(void** state);
void test_algo_mismatch__cstr_mismatch(void** state);
void test_algo_mismatch__cstr_match(void** state);
void test_algo_mismatch__cstl_builtin_mismatch(void** state);
void test_algo_mismatch__cstl_builtin_match(void** state);
void test_algo_mismatch__user_define_mismatch(void** state);
void test_algo_mismatch__user_define_match(void** state);
/*
 * test algo_mismatch_if
 */
UT_CASE_DECLARATION(algo_mismatch_if)
void test_algo_mismatch_if__invalid_first_range(void** state);
void test_algo_mismatch_if__invalid_first_range2(void** state);
void test_algo_mismatch_if__invalid_range_not_same_type(void** state);
void test_algo_mismatch_if__first_range_empty(void** state);
void test_algo_mismatch_if__bfun_NULL_mismatch(void** state);
void test_algo_mismatch_if__bfun_NULL_match(void** state);
void test_algo_mismatch_if__c_builtin_mismatch(void** state);
void test_algo_mismatch_if__c_builtin_match(void** state);
void test_algo_mismatch_if__cstr_mismatch(void** state);
void test_algo_mismatch_if__cstr_match(void** state);
void test_algo_mismatch_if__cstl_builtin_mismatch(void** state);
void test_algo_mismatch_if__cstl_builtin_match(void** state);
void test_algo_mismatch_if__user_define_mismatch(void** state);
void test_algo_mismatch_if__user_define_match(void** state);
/*
 * test algo_equal
 */
UT_CASE_DECLARATION(algo_equal)
void test_algo_equal__invalid_first_range(void** state);
void test_algo_equal__invalid_first_range2(void** state);
void test_algo_equal__invalid_range_not_same_type(void** state);
void test_algo_equal__first_range_empty(void** state);
void test_algo_equal__c_builtin_equal(void** state);
void test_algo_equal__c_builtin_unequal(void** state);
void test_algo_equal__cstr_equal(void** state);
void test_algo_equal__cstr_unequal(void** state);
void test_algo_equal__cstl_builtin_equal(void** state);
void test_algo_equal__cstl_builtin_unequal(void** state);
void test_algo_equal__user_define_equal(void** state);
void test_algo_equal__user_define_unequal(void** state);
/*
 * test algo_equal_if
 */
UT_CASE_DECLARATION(algo_equal_if)
void test_algo_equal_if__invalid_first_range(void** state);
void test_algo_equal_if__invalid_first_range2(void** state);
void test_algo_equal_if__invalid_range_not_same_type(void** state);
void test_algo_equal_if__first_range_empty(void** state);
void test_algo_equal_if__bfun_NULL_equal(void** state);
void test_algo_equal_if__bfun_NULL_unequal(void** state);
void test_algo_equal_if__c_builtin_equal(void** state);
void test_algo_equal_if__c_builtin_unequal(void** state);
void test_algo_equal_if__cstr_equal(void** state);
void test_algo_equal_if__cstr_unequal(void** state);
void test_algo_equal_if__cstl_builtin_equal(void** state);
void test_algo_equal_if__cstl_builtin_unequal(void** state);
void test_algo_equal_if__user_define_equal(void** state);
void test_algo_equal_if__user_define_unequal(void** state);
/*
 * test algo_search
 */
UT_CASE_DECLARATION(algo_search)
void test_algo_search__invalid_first_range(void** state);
void test_algo_search__invalid_first_range2(void** state);
void test_algo_search__invalid_first_range3(void** state);
void test_algo_search__invalid_second_range(void** state);
void test_algo_search__invalid_second_range2(void** state);
void test_algo_search__invalid_second_range3(void** state);
void test_algo_search__invalid_range_not_same_type(void** state);
void test_algo_search__first_range_empty(void** state);
void test_algo_search__second_range_empty(void** state);
void test_algo_search__c_builtin_match(void** state);
void test_algo_search__c_builtin_mismatch(void** state);
void test_algo_search__cstr_match(void** state);
void test_algo_search__cstr_mismatch(void** state);
void test_algo_search__cstl_builtin_match(void** state);
void test_algo_search__cstl_builtin_mismatch(void** state);
void test_algo_search__user_define_match(void** state);
void test_algo_search__user_define_mismatch(void** state);
/*
 * test algo_search_if
 */
UT_CASE_DECLARATION(algo_search_if)
void test_algo_search_if__invalid_first_range(void** state);
void test_algo_search_if__invalid_first_range2(void** state);
void test_algo_search_if__invalid_first_range3(void** state);
void test_algo_search_if__invalid_second_range(void** state);
void test_algo_search_if__invalid_second_range2(void** state);
void test_algo_search_if__invalid_second_range3(void** state);
void test_algo_search_if__invalid_range_not_same_type(void** state);
void test_algo_search_if__first_range_empty(void** state);
void test_algo_search_if__second_range_empty(void** state);
void test_algo_search_if__bfun_NULL_match(void** state);
void test_algo_search_if__bfun_NULL_mismatch(void** state);
void test_algo_search_if__c_builtin_match(void** state);
void test_algo_search_if__c_builtin_mismatch(void** state);
void test_algo_search_if__cstr_match(void** state);
void test_algo_search_if__cstr_mismatch(void** state);
void test_algo_search_if__cstl_builtin_match(void** state);
void test_algo_search_if__cstl_builtin_mismatch(void** state);
void test_algo_search_if__user_define_match(void** state);
void test_algo_search_if__user_define_mismatch(void** state);
/*
 * test algo_search_end and algo_find_end
 */
UT_CASE_DECLARATION(algo_search_end_algo_find_end)
void test_algo_search_end_algo_find_end__invalid_first_range(void** state);
void test_algo_search_end_algo_find_end__invalid_first_range2(void** state);
void test_algo_search_end_algo_find_end__invalid_first_range3(void** state);
void test_algo_search_end_algo_find_end__invalid_second_range(void** state);
void test_algo_search_end_algo_find_end__invalid_second_range2(void** state);
void test_algo_search_end_algo_find_end__invalid_second_range3(void** state);
void test_algo_search_end_algo_find_end__invalid_range_not_same_type(void** state);
void test_algo_search_end_algo_find_end__first_range_empty(void** state);
void test_algo_search_end_algo_find_end__second_range_empty(void** state);
void test_algo_search_end_algo_find_end__c_builtin_match(void** state);
void test_algo_search_end_algo_find_end__c_builtin_mismatch(void** state);
void test_algo_search_end_algo_find_end__cstr_match(void** state);
void test_algo_search_end_algo_find_end__cstr_mismatch(void** state);
void test_algo_search_end_algo_find_end__cstl_builtin_match(void** state);
void test_algo_search_end_algo_find_end__cstl_builtin_mismatch(void** state);
void test_algo_search_end_algo_find_end__user_define_match(void** state);
void test_algo_search_end_algo_find_end__user_define_mismatch(void** state);
/*
 * test algo_search_end_if and algo_find_end_if
 */
UT_CASE_DECLARATION(algo_search_end_if_algo_find_end_if)
void test_algo_search_end_if_algo_find_end_if__invalid_first_range(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_first_range2(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_first_range3(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_second_range(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_second_range2(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_second_range3(void** state);
void test_algo_search_end_if_algo_find_end_if__invalid_range_not_same_type(void** state);
void test_algo_search_end_if_algo_find_end_if__first_range_empty(void** state);
void test_algo_search_end_if_algo_find_end_if__second_range_empty(void** state);
void test_algo_search_end_if_algo_find_end_if__bfun_NULL_match(void** state);
void test_algo_search_end_if_algo_find_end_if__bfun_NULL_mismatch(void** state);
void test_algo_search_end_if_algo_find_end_if__c_builtin_match(void** state);
void test_algo_search_end_if_algo_find_end_if__c_builtin_mismatch(void** state);
void test_algo_search_end_if_algo_find_end_if__cstr_match(void** state);
void test_algo_search_end_if_algo_find_end_if__cstr_mismatch(void** state);
void test_algo_search_end_if_algo_find_end_if__cstl_builtin_match(void** state);
void test_algo_search_end_if_algo_find_end_if__cstl_builtin_mismatch(void** state);
void test_algo_search_end_if_algo_find_end_if__user_define_match(void** state);
void test_algo_search_end_if_algo_find_end_if__user_define_mismatch(void** state);

#define UT_CSTL_ALGO_NONMUTATING_CASE\
    UT_SUIT_BEGIN(cstl_algo_nonmutating, test_algo_for_each__invalid_range),\
    UT_CASE(test_algo_for_each__invalid_range_2),\
    UT_CASE(test_algo_for_each__empty_range),\
    UT_CASE(test_algo_for_each__ufun_NULL),\
    UT_CASE(test_algo_for_each__mutate_all),\
    UT_CASE(test_algo_for_each__mutate_partial),\
    UT_CASE(test_algo_for_each__cstr),\
    UT_CASE(test_algo_for_each__cstl_builtin),\
    UT_CASE(test_algo_for_each__user_define),\
    UT_CASE_BEGIN(algo_find_if, test_algo_find_if__invalid_range),\
    UT_CASE(test_algo_find_if__invalid_range_2),\
    UT_CASE(test_algo_find_if__empty_range),\
    UT_CASE(test_algo_find_if__ufun_NULL),\
    UT_CASE(test_algo_find_if__c_builtin_found),\
    UT_CASE(test_algo_find_if__c_builtin_not_found),\
    UT_CASE(test_algo_find_if__cstr_found),\
    UT_CASE(test_algo_find_if__cstr_not_found),\
    UT_CASE(test_algo_find_if__cstl_builtin_found),\
    UT_CASE(test_algo_find_if__cstl_builtin_not_found),\
    UT_CASE(test_algo_find_if__user_define_found),\
    UT_CASE(test_algo_find_if__user_define_not_found),\
    UT_CASE_BEGIN(algo_adjacent_find, test_algo_adjacent_find__invalid_range_invalid_iter),\
    UT_CASE(test_algo_adjacent_find__invalid_range_not_belong_to_same_container),\
    UT_CASE(test_algo_adjacent_find__invalid_range_reverse),\
    UT_CASE(test_algo_adjacent_find__c_builtin_found),\
    UT_CASE(test_algo_adjacent_find__c_builtin_not_found),\
    UT_CASE(test_algo_adjacent_find__cstr_found),\
    UT_CASE(test_algo_adjacent_find__cstr_not_found),\
    UT_CASE(test_algo_adjacent_find__cstl_builtin_found),\
    UT_CASE(test_algo_adjacent_find__cstl_builtin_not_found),\
    UT_CASE(test_algo_adjacent_find__user_define_found),\
    UT_CASE(test_algo_adjacent_find__user_define_not_found),\
    UT_CASE(test_algo_adjacent_find__empty),\
    UT_CASE_BEGIN(algo_adjacent_find_if, test_algo_adjacent_find_if__invalid_range_invalid_iter),\
    UT_CASE(test_algo_adjacent_find_if__invalid_range_not_belong_to_same_container),\
    UT_CASE(test_algo_adjacent_find_if__invalid_range_reverse),\
    UT_CASE(test_algo_adjacent_find_if__empty),\
    UT_CASE(test_algo_adjacent_find_if__bfun_NULL_found),\
    UT_CASE(test_algo_adjacent_find_if__bfun_NULL_not_found),\
    UT_CASE(test_algo_adjacent_find_if__c_builtin_found),\
    UT_CASE(test_algo_adjacent_find_if__c_builtin_not_found),\
    UT_CASE(test_algo_adjacent_find_if__cstr_found),\
    UT_CASE(test_algo_adjacent_find_if__cstr_not_found),\
    UT_CASE(test_algo_adjacent_find_if__cstl_builtin_found),\
    UT_CASE(test_algo_adjacent_find_if__cstl_builtin_not_found),\
    UT_CASE(test_algo_adjacent_find_if__user_define_found),\
    UT_CASE(test_algo_adjacent_find_if__user_define_not_found),\
    UT_CASE_BEGIN(algo_find_first_of, test_algo_find_first_of__invalid_first_range_not_belong_to_same),\
    UT_CASE(test_algo_find_first_of__invalid_first_range_reverse),\
    UT_CASE(test_algo_find_first_of__invalid_second_range_invalid_iter),\
    UT_CASE(test_algo_find_first_of__invalid_second_range_not_belong_to_same),\
    UT_CASE(test_algo_find_first_of__invalid_second_range_reverse),\
    UT_CASE(test_algo_find_first_of__first_range_empty),\
    UT_CASE(test_algo_find_first_of__second_range_empty),\
    UT_CASE(test_algo_find_first_of__c_builtin_found),\
    UT_CASE(test_algo_find_first_of__c_builtin_not_found),\
    UT_CASE(test_algo_find_first_of__cstr_found),\
    UT_CASE(test_algo_find_first_of__cstr_not_found),\
    UT_CASE(test_algo_find_first_of__cstl_builtin_found),\
    UT_CASE(test_algo_find_first_of__cstl_builtin_not_found),\
    UT_CASE(test_algo_find_first_of__user_define_found),\
    UT_CASE(test_algo_find_first_of__user_define_not_found),\
    UT_CASE_BEGIN(algo_find_first_of_if, test_algo_find_first_of_if__invalid_first_range_not_belong_to_same),\
    UT_CASE(test_algo_find_first_of_if__invalid_first_range_reverse),\
    UT_CASE(test_algo_find_first_of_if__invalid_second_range_invalid_iter),\
    UT_CASE(test_algo_find_first_of_if__invalid_second_range_not_belong_to_same),\
    UT_CASE(test_algo_find_first_of_if__invalid_second_range_reverse),\
    UT_CASE(test_algo_find_first_of_if__first_range_empty),\
    UT_CASE(test_algo_find_first_of_if__second_range_empty),\
    UT_CASE(test_algo_find_first_of_if__bfun_NULL_found),\
    UT_CASE(test_algo_find_first_of_if__bfun_NULL_not_found),\
    UT_CASE(test_algo_find_first_of_if__c_builtin_found),\
    UT_CASE(test_algo_find_first_of_if__c_builtin_not_found),\
    UT_CASE(test_algo_find_first_of_if__cstr_found),\
    UT_CASE(test_algo_find_first_of_if__cstr_not_found),\
    UT_CASE(test_algo_find_first_of_if__cstl_builtin_found),\
    UT_CASE(test_algo_find_first_of_if__cstl_builtin_not_found),\
    UT_CASE(test_algo_find_first_of_if__user_define_found),\
    UT_CASE(test_algo_find_first_of_if__user_define_not_found),\
    UT_CASE(test_algo_find_first_of_if__not_same_type),\
    UT_CASE_BEGIN(algo_count_if, test_algo_count_if__invalid_range),\
    UT_CASE(test_algo_count_if__invalid_range2),\
    UT_CASE(test_algo_count_if__empty),\
    UT_CASE(test_algo_count_if__ufun_NULL),\
    UT_CASE(test_algo_count_if__c_builtin_0),\
    UT_CASE(test_algo_count_if__c_builtin_1),\
    UT_CASE(test_algo_count_if__c_builtin_n),\
    UT_CASE(test_algo_count_if__cstr_0),\
    UT_CASE(test_algo_count_if__cstr_1),\
    UT_CASE(test_algo_count_if__cstr_n),\
    UT_CASE(test_algo_count_if__cstl_builtin_0),\
    UT_CASE(test_algo_count_if__cstl_builtin_1),\
    UT_CASE(test_algo_count_if__cstl_builtin_n),\
    UT_CASE(test_algo_count_if__user_define_0),\
    UT_CASE(test_algo_count_if__user_define_1),\
    UT_CASE(test_algo_count_if__user_define_n),\
    UT_CASE_BEGIN(algo_mismatch, test_algo_mismatch__invalid_first_range),\
    UT_CASE(test_algo_mismatch__invalid_first_range2),\
    UT_CASE(test_algo_mismatch__first_range_empty),\
    UT_CASE(test_algo_mismatch__invalid_range_not_same_type),\
    UT_CASE(test_algo_mismatch__c_builtin_mismatch),\
    UT_CASE(test_algo_mismatch__c_builtin_match),\
    UT_CASE(test_algo_mismatch__cstr_mismatch),\
    UT_CASE(test_algo_mismatch__cstr_match),\
    UT_CASE(test_algo_mismatch__cstl_builtin_mismatch),\
    UT_CASE(test_algo_mismatch__cstl_builtin_match),\
    UT_CASE(test_algo_mismatch__user_define_mismatch),\
    UT_CASE(test_algo_mismatch__user_define_match),\
    UT_CASE_BEGIN(algo_mismatch_if, test_algo_mismatch_if__invalid_first_range),\
    UT_CASE(test_algo_mismatch_if__invalid_first_range2),\
    UT_CASE(test_algo_mismatch_if__invalid_range_not_same_type),\
    UT_CASE(test_algo_mismatch_if__first_range_empty),\
    UT_CASE(test_algo_mismatch_if__bfun_NULL_mismatch),\
    UT_CASE(test_algo_mismatch_if__bfun_NULL_match),\
    UT_CASE(test_algo_mismatch_if__c_builtin_mismatch),\
    UT_CASE(test_algo_mismatch_if__c_builtin_match),\
    UT_CASE(test_algo_mismatch_if__cstr_mismatch),\
    UT_CASE(test_algo_mismatch_if__cstr_match),\
    UT_CASE(test_algo_mismatch_if__cstl_builtin_mismatch),\
    UT_CASE(test_algo_mismatch_if__cstl_builtin_match),\
    UT_CASE(test_algo_mismatch_if__user_define_mismatch),\
    UT_CASE(test_algo_mismatch_if__user_define_match),\
    UT_CASE_BEGIN(algo_equal, test_algo_equal__invalid_first_range),\
    UT_CASE(test_algo_equal__invalid_first_range2),\
    UT_CASE(test_algo_equal__invalid_range_not_same_type),\
    UT_CASE(test_algo_equal__first_range_empty),\
    UT_CASE(test_algo_equal__c_builtin_equal),\
    UT_CASE(test_algo_equal__c_builtin_unequal),\
    UT_CASE(test_algo_equal__cstr_equal),\
    UT_CASE(test_algo_equal__cstr_unequal),\
    UT_CASE(test_algo_equal__cstl_builtin_equal),\
    UT_CASE(test_algo_equal__cstl_builtin_unequal),\
    UT_CASE(test_algo_equal__user_define_equal),\
    UT_CASE(test_algo_equal__user_define_unequal),\
    UT_CASE_BEGIN(algo_equal_if, test_algo_equal_if__invalid_first_range),\
    UT_CASE(test_algo_equal_if__invalid_first_range2),\
    UT_CASE(test_algo_equal_if__invalid_range_not_same_type),\
    UT_CASE(test_algo_equal_if__first_range_empty),\
    UT_CASE(test_algo_equal_if__bfun_NULL_equal),\
    UT_CASE(test_algo_equal_if__bfun_NULL_unequal),\
    UT_CASE(test_algo_equal_if__c_builtin_equal),\
    UT_CASE(test_algo_equal_if__c_builtin_unequal),\
    UT_CASE(test_algo_equal_if__cstr_equal),\
    UT_CASE(test_algo_equal_if__cstr_unequal),\
    UT_CASE(test_algo_equal_if__cstl_builtin_equal),\
    UT_CASE(test_algo_equal_if__cstl_builtin_unequal),\
    UT_CASE(test_algo_equal_if__user_define_equal),\
    UT_CASE(test_algo_equal_if__user_define_unequal),\
    UT_CASE_BEGIN(algo_search, test_algo_search__invalid_first_range),\
    UT_CASE(test_algo_search__invalid_first_range2),\
    UT_CASE(test_algo_search__invalid_first_range3),\
    UT_CASE(test_algo_search__invalid_second_range),\
    UT_CASE(test_algo_search__invalid_second_range2),\
    UT_CASE(test_algo_search__invalid_second_range3),\
    UT_CASE(test_algo_search__invalid_range_not_same_type),\
    UT_CASE(test_algo_search__first_range_empty),\
    UT_CASE(test_algo_search__second_range_empty),\
    UT_CASE(test_algo_search__c_builtin_match),\
    UT_CASE(test_algo_search__c_builtin_mismatch),\
    UT_CASE(test_algo_search__cstr_match),\
    UT_CASE(test_algo_search__cstr_mismatch),\
    UT_CASE(test_algo_search__cstl_builtin_match),\
    UT_CASE(test_algo_search__cstl_builtin_mismatch),\
    UT_CASE(test_algo_search__user_define_match),\
    UT_CASE(test_algo_search__user_define_mismatch),\
    UT_CASE_BEGIN(algo_search_if, test_algo_search_if__invalid_first_range),\
    UT_CASE(test_algo_search_if__invalid_first_range2),\
    UT_CASE(test_algo_search_if__invalid_first_range3),\
    UT_CASE(test_algo_search_if__invalid_second_range),\
    UT_CASE(test_algo_search_if__invalid_second_range2),\
    UT_CASE(test_algo_search_if__invalid_second_range3),\
    UT_CASE(test_algo_search_if__invalid_range_not_same_type),\
    UT_CASE(test_algo_search_if__first_range_empty),\
    UT_CASE(test_algo_search_if__second_range_empty),\
    UT_CASE(test_algo_search_if__bfun_NULL_match),\
    UT_CASE(test_algo_search_if__bfun_NULL_mismatch),\
    UT_CASE(test_algo_search_if__c_builtin_match),\
    UT_CASE(test_algo_search_if__c_builtin_mismatch),\
    UT_CASE(test_algo_search_if__cstr_match),\
    UT_CASE(test_algo_search_if__cstr_mismatch),\
    UT_CASE(test_algo_search_if__cstl_builtin_match),\
    UT_CASE(test_algo_search_if__cstl_builtin_mismatch),\
    UT_CASE(test_algo_search_if__user_define_match),\
    UT_CASE(test_algo_search_if__user_define_mismatch),\
    UT_CASE_BEGIN(algo_search_end_algo_find_end, test_algo_search_end_algo_find_end__invalid_first_range),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_first_range2),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_first_range3),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_second_range),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_second_range2),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_second_range3),\
    UT_CASE(test_algo_search_end_algo_find_end__invalid_range_not_same_type),\
    UT_CASE(test_algo_search_end_algo_find_end__first_range_empty),\
    UT_CASE(test_algo_search_end_algo_find_end__second_range_empty),\
    UT_CASE(test_algo_search_end_algo_find_end__c_builtin_match),\
    UT_CASE(test_algo_search_end_algo_find_end__c_builtin_mismatch),\
    UT_CASE(test_algo_search_end_algo_find_end__cstr_match),\
    UT_CASE(test_algo_search_end_algo_find_end__cstr_mismatch),\
    UT_CASE(test_algo_search_end_algo_find_end__cstl_builtin_match),\
    UT_CASE(test_algo_search_end_algo_find_end__cstl_builtin_mismatch),\
    UT_CASE(test_algo_search_end_algo_find_end__user_define_match),\
    UT_CASE(test_algo_search_end_algo_find_end__user_define_mismatch),\
    UT_CASE_BEGIN(algo_search_end_if_algo_find_end_if, test_algo_search_end_if_algo_find_end_if__invalid_first_range),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_first_range2),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_first_range3),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_second_range),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_second_range2),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_second_range3),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__invalid_range_not_same_type),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__first_range_empty),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__second_range_empty),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__bfun_NULL_match),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__bfun_NULL_mismatch),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__c_builtin_match),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__c_builtin_mismatch),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__cstr_match),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__cstr_mismatch),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__cstl_builtin_match),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__cstl_builtin_mismatch),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__user_define_match),\
    UT_CASE(test_algo_search_end_if_algo_find_end_if__user_define_mismatch)

#endif /* _UT_CSTL_ALGO_NONMUTATING_H_ */
