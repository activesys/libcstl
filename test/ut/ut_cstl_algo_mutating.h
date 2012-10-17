#ifndef _UT_CSTL_ALGO_MUTATING_H_
#define _UT_CSTL_ALGO_MUTATING_H_

UT_SUIT_DECLARATION(cstl_algo_mutating)

/*
 * test algo_copy
 */
UT_CASE_DECLARATION(algo_copy)
void test_algo_copy__invalid_source_range(void** state);
void test_algo_copy__invalid_source_range2(void** state);
void test_algo_copy__invalid_source_range3(void** state);
void test_algo_copy__invalid_dest_range(void** state);
void test_algo_copy__invalid_range_not_same_type(void** state);
void test_algo_copy__source_range_empty(void** state);
void test_algo_copy__overlapping_left(void** state);
void test_algo_copy__overlapping_right(void** state);
void test_algo_copy__c_builtin(void** state);
void test_algo_copy__cstr(void** state);
void test_algo_copy__cstl_builtin(void** state);
void test_algo_copy__user_define(void** state);
/*
 * test algo_copy_n
 */
UT_CASE_DECLARATION(algo_copy_n)
void test_algo_copy_n__invalid_source_range(void** state);
void test_algo_copy_n__invalid_dest_range(void** state);
void test_algo_copy_n__invalid_range_not_same_type(void** state);
void test_algo_copy_n__source_range_empty(void** state);
void test_algo_copy_n__overlapping_left(void** state);
void test_algo_copy_n__overlapping_right(void** state);
void test_algo_copy_n__c_builtin(void** state);
void test_algo_copy_n__cstr(void** state);
void test_algo_copy_n__cstl_builtin(void** state);
void test_algo_copy_n__user_define(void** state);
/*
 * test algo_copy_backward
 */
UT_CASE_DECLARATION(algo_copy_backward)
void test_algo_copy_backward__invalid_source_range(void** state);
void test_algo_copy_backward__invalid_source_range2(void** state);
void test_algo_copy_backward__invalid_source_range3(void** state);
void test_algo_copy_backward__invalid_dest_range(void** state);
void test_algo_copy_backward__invalid_range_not_same_type(void** state);
void test_algo_copy_backward__source_range_empty(void** state);
void test_algo_copy_backward__overlapping_left(void** state);
void test_algo_copy_backward__overlapping_right(void** state);
void test_algo_copy_backward__c_builtin(void** state);
void test_algo_copy_backward__cstr(void** state);
void test_algo_copy_backward__cstl_builtin(void** state);
void test_algo_copy_backward__user_define(void** state);
/*
 * test algo_swap and algo_iter_swap
 */
UT_CASE_DECLARATION(algo_swap_algo_iter_swap)
void test_algo_swap_algo_iter_swap__invalid_first(void** state);
void test_algo_swap_algo_iter_swap__invalid_second(void** state);
void test_algo_swap_algo_iter_swap__not_same_type(void** state);
void test_algo_swap_algo_iter_swap__c_builtin(void** state);
void test_algo_swap_algo_iter_swap__cstr(void** state);
void test_algo_swap_algo_iter_swap__cstl_builtin(void** state);
void test_algo_swap_algo_iter_swap__user_define(void** state);
/*
 * test algo_swap_ranges
 */
UT_CASE_DECLARATION(algo_swap_ranges)
void test_algo_swap_ranges__invalid_first_range(void** state);
void test_algo_swap_ranges__invalid_first_range2(void** state);
void test_algo_swap_ranges__invalid_first_range3(void** state);
void test_algo_swap_ranges__invalid_second_range(void** state);
void test_algo_swap_ranges__invalid_range_not_same_type(void** state);
void test_algo_swap_ranges__first_range_empty(void** state);
void test_algo_swap_ranges__c_builtin(void** state);
void test_algo_swap_ranges__cstr(void** state);
void test_algo_swap_ranges__cstl_builtin(void** state);
void test_algo_swap_ranges__user_define(void** state);
/*
 * test algo_transform
 */
UT_CASE_DECLARATION(algo_transform)
void test_algo_transform__invalid_source_range(void** state);
void test_algo_transform__invalid_source_range2(void** state);
void test_algo_transform__invalid_source_range3(void** state);
void test_algo_transform__invalid_dest_range(void** state);
void test_algo_transform__invalid_range_not_same_type(void** state);
void test_algo_transform__source_range_empty(void** state);
void test_algo_transform__ufun_NULL(void** state);
void test_algo_transform__c_builtin(void** state);
void test_algo_transform__cstr(void** state);
void test_algo_transform__cstl_builtin(void** state);
void test_algo_transform__user_define(void** state);

#define UT_CSTL_ALGO_MUTATING_CASE\
    UT_SUIT_BEGIN(cstl_algo_mutating, test_algo_copy__invalid_source_range),\
    UT_CASE(test_algo_copy__invalid_source_range2),\
    UT_CASE(test_algo_copy__invalid_source_range3),\
    UT_CASE(test_algo_copy__invalid_dest_range),\
    UT_CASE(test_algo_copy__invalid_range_not_same_type),\
    UT_CASE(test_algo_copy__source_range_empty),\
    UT_CASE(test_algo_copy__overlapping_left),\
    UT_CASE(test_algo_copy__overlapping_right),\
    UT_CASE(test_algo_copy__c_builtin),\
    UT_CASE(test_algo_copy__cstr),\
    UT_CASE(test_algo_copy__cstl_builtin),\
    UT_CASE(test_algo_copy__user_define),\
    UT_CASE_BEGIN(algo_copy_n, test_algo_copy_n__invalid_source_range),\
    UT_CASE(test_algo_copy_n__invalid_dest_range),\
    UT_CASE(test_algo_copy_n__invalid_range_not_same_type),\
    UT_CASE(test_algo_copy_n__source_range_empty),\
    UT_CASE(test_algo_copy_n__overlapping_left),\
    UT_CASE(test_algo_copy_n__overlapping_right),\
    UT_CASE(test_algo_copy_n__c_builtin),\
    UT_CASE(test_algo_copy_n__cstr),\
    UT_CASE(test_algo_copy_n__cstl_builtin),\
    UT_CASE(test_algo_copy_n__user_define),\
    UT_CASE_BEGIN(algo_copy_backward, test_algo_copy_backward__invalid_source_range),\
    UT_CASE(test_algo_copy_backward__invalid_source_range2),\
    UT_CASE(test_algo_copy_backward__invalid_source_range3),\
    UT_CASE(test_algo_copy_backward__invalid_dest_range),\
    UT_CASE(test_algo_copy_backward__invalid_range_not_same_type),\
    UT_CASE(test_algo_copy_backward__source_range_empty),\
    UT_CASE(test_algo_copy_backward__overlapping_left),\
    UT_CASE(test_algo_copy_backward__overlapping_right),\
    UT_CASE(test_algo_copy_backward__c_builtin),\
    UT_CASE(test_algo_copy_backward__cstr),\
    UT_CASE(test_algo_copy_backward__cstl_builtin),\
    UT_CASE(test_algo_copy_backward__user_define),\
    UT_CASE_BEGIN(algo_swap_algo_iter_swap, test_algo_swap_algo_iter_swap__invalid_first),\
    UT_CASE(test_algo_swap_algo_iter_swap__invalid_second),\
    UT_CASE(test_algo_swap_algo_iter_swap__not_same_type),\
    UT_CASE(test_algo_swap_algo_iter_swap__c_builtin),\
    UT_CASE(test_algo_swap_algo_iter_swap__cstr),\
    UT_CASE(test_algo_swap_algo_iter_swap__cstl_builtin),\
    UT_CASE(test_algo_swap_algo_iter_swap__user_define),\
    UT_CASE_BEGIN(algo_swap_ranges, test_algo_swap_ranges__invalid_first_range),\
    UT_CASE(test_algo_swap_ranges__invalid_first_range2),\
    UT_CASE(test_algo_swap_ranges__invalid_first_range3),\
    UT_CASE(test_algo_swap_ranges__invalid_second_range),\
    UT_CASE(test_algo_swap_ranges__invalid_range_not_same_type),\
    UT_CASE(test_algo_swap_ranges__first_range_empty),\
    UT_CASE(test_algo_swap_ranges__c_builtin),\
    UT_CASE(test_algo_swap_ranges__cstr),\
    UT_CASE(test_algo_swap_ranges__cstl_builtin),\
    UT_CASE(test_algo_swap_ranges__user_define),\
    UT_CASE_BEGIN(algo_transform, test_algo_transform__invalid_source_range),\
    UT_CASE(test_algo_transform__invalid_source_range2),\
    UT_CASE(test_algo_transform__invalid_source_range3),\
    UT_CASE(test_algo_transform__invalid_dest_range),\
    UT_CASE(test_algo_transform__invalid_range_not_same_type),\
    UT_CASE(test_algo_transform__source_range_empty),\
    UT_CASE(test_algo_transform__ufun_NULL),\
    UT_CASE(test_algo_transform__c_builtin),\
    UT_CASE(test_algo_transform__cstr),\
    UT_CASE(test_algo_transform__cstl_builtin),\
    UT_CASE(test_algo_transform__user_define)

#endif /* _UT_CSTL_ALGO_MUTATING_H_ */

