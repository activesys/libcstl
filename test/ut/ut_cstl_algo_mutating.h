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
/*
 * test algo_transform_binary
 */
UT_CASE_DECLARATION(algo_transform_binary)
void test_algo_transform_binary__invalid_first_range(void** state);
void test_algo_transform_binary__invalid_first_range2(void** state);
void test_algo_transform_binary__invalid_first_range3(void** state);
void test_algo_transform_binary__invalid_second_range(void** state);
void test_algo_transform_binary__invalid_dest_range(void** state);
void test_algo_transform_binary__invalid_range_not_same_type(void** state);
void test_algo_transform_binary__invalid_range_not_same_type2(void** state);
void test_algo_transform_binary__first_range_empty(void** state);
void test_algo_transform_binary__bfun_NULL(void** state);
void test_algo_transform_binary__c_builtin(void** state);
void test_algo_transform_binary__cstr(void** state);
void test_algo_transform_binary__cstl_builtin(void** state);
void test_algo_transform_binary__user_define(void** state);
/*
 * test algo_replace
 */
UT_CASE_DECLARATION(algo_replace)
void test_algo_replace__invalid_range(void** state);
void test_algo_replace__invalid_range2(void** state);
void test_algo_replace__invalid_range3(void** state);
void test_algo_replace__c_builtin(void** state);
void test_algo_replace__cstr(void** state);
void test_algo_replace__cstl_builtin(void** state);
void test_algo_replace__user_define(void** state);
/*
 * test algo_replace_copy
 */
UT_CASE_DECLARATION(algo_replace_copy)
void test_algo_replace_copy__invalid_source_range(void** state);
void test_algo_replace_copy__invalid_source_range2(void** state);
void test_algo_replace_copy__invalid_source_range3(void** state);
void test_algo_replace_copy__invalid_dest_range(void** state);
void test_algo_replace_copy__invalid_range_not_same_type(void** state);
void test_algo_replace_copy__source_range_empty(void** state);
void test_algo_replace_copy__c_builtin(void** state);
void test_algo_replace_copy__cstr(void** state);
void test_algo_replace_copy__cstl_builtin(void** state);
void test_algo_replace_copy__user_define(void** state);
/*
 * test algo_generate
 */
UT_CASE_DECLARATION(algo_generate)
void test_algo_generate__invalid_range(void** state);
void test_algo_generate__invalid_range2(void** state);
void test_algo_generate__invalid_range3(void** state);
void test_algo_generate__range_empty(void** state);
void test_algo_generate__ufun_NULL(void** state);
void test_algo_generate__c_builtin(void** state);
void test_algo_generate__cstr(void** state);
void test_algo_generate__cstl_builtin(void** state);
void test_algo_generate__user_define(void** state);
/*
 * test algo_generate_n
 */
UT_CASE_DECLARATION(algo_generate_n)
void test_algo_generate_n__invalid_range(void** state);
void test_algo_generate_n__empty(void** state);
void test_algo_generate_n__ufun_NULL(void** state);
void test_algo_generate_n__c_builtin(void** state);
void test_algo_generate_n__cstr(void** state);
void test_algo_generate_n__cstl_builtin(void** state);
void test_algo_generate_n__user_define(void** state);
/*
 * test algo_remove_if
 */
UT_CASE_DECLARATION(algo_remove_if)
void test_algo_remove_if__invalid_range(void** state);
void test_algo_remove_if__invalid_range2(void** state);
void test_algo_remove_if__invalid_range3(void** state);
void test_algo_remove_if__empty(void** state);
void test_algo_remove_if__ufun_NULL(void** state);
void test_algo_remove_if__c_builtin(void** state);
void test_algo_remove_if__cstr(void** state);
void test_algo_remove_if__cstl_builtin(void** state);
void test_algo_remove_if__user_define(void** state);
/*
 * test algo_remove_copy_if
 */
UT_CASE_DECLARATION(algo_remove_copy_if)
void test_algo_remove_copy_if__invalid_source_range(void** state);
void test_algo_remove_copy_if__invalid_source_range2(void** state);
void test_algo_remove_copy_if__invalid_source_range3(void** state);
void test_algo_remove_copy_if__invalid_dest_range(void** state);
void test_algo_remove_copy_if__invalid_range_not_same_type(void** state);
void test_algo_remove_copy_if__source_range_empty(void** state);
void test_algo_remove_copy_if__ufun_NULL(void** state);
void test_algo_remove_copy_if__c_builtin(void** state);
void test_algo_remove_copy_if__cstr(void** state);
void test_algo_remove_copy_if__cstl_builtin(void** state);
void test_algo_remove_copy_if__user_define(void** state);
/*
 * test algo_unique
 */
UT_CASE_DECLARATION(algo_unique)
void test_algo_unique__invalid_range(void** state);
void test_algo_unique__invalid_range2(void** state);
void test_algo_unique__invalid_range3(void** state);
void test_algo_unique__empty(void** state);
void test_algo_unique__no_duplication(void** state);
void test_algo_unique__c_builtin(void** state);
void test_algo_unique__cstr(void** state);
void test_algo_unique__cstl_builtin(void** state);
void test_algo_unique__user_define(void** state);
/*
 * test algo_unique_if
 */
UT_CASE_DECLARATION(algo_unique_if)
void test_algo_unique_if__invalid_range(void** state);
void test_algo_unique_if__invalid_range2(void** state);
void test_algo_unique_if__invalid_range3(void** state);
void test_algo_unique_if__empty(void** state);
void test_algo_unique_if__bfun_NULL(void** state);
void test_algo_unique_if__c_builtin(void** state);
void test_algo_unique_if__cstr(void** state);
void test_algo_unique_if__cstl_builtin(void** state);
void test_algo_unique_if__user_define(void** state);
/*
 * test algo_unique_copy
 */
UT_CASE_DECLARATION(algo_unique_copy)
void test_algo_unique_copy__invalid_range(void** state);
void test_algo_unique_copy__invalid_range2(void** state);
void test_algo_unique_copy__invalid_range3(void** state);
void test_algo_unique_copy__invalid_dest_range(void** state);
void test_algo_unique_copy__not_same_type(void** state);
void test_algo_unique_copy__empty(void** state);
void test_algo_unique_copy__no_duplication(void** state);
void test_algo_unique_copy__c_builtin(void** state);
void test_algo_unique_copy__cstr(void** state);
void test_algo_unique_copy__cstl_builtin(void** state);
void test_algo_unique_copy__user_define(void** state);
/*
 * test algo_unique_copy_if
 */
UT_CASE_DECLARATION(algo_unique_copy_if)
void test_algo_unique_copy_if__invalid_range(void** state);
void test_algo_unique_copy_if__invalid_range2(void** state);
void test_algo_unique_copy_if__invalid_range3(void** state);
void test_algo_unique_copy_if__invalid_dest_range(void** state);
void test_algo_unique_copy_if__not_same_type(void** state);
void test_algo_unique_copy_if__empty(void** state);
void test_algo_unique_copy_if__bfun_NULL(void** state);
void test_algo_unique_copy_if__c_builtin(void** state);
void test_algo_unique_copy_if__cstr(void** state);
void test_algo_unique_copy_if__cstl_builtin(void** state);
void test_algo_unique_copy_if__user_define(void** state);
/*
 * test algo_reverse
 */
UT_CASE_DECLARATION(algo_reverse)
void test_algo_reverse__invalid_range(void** state);
void test_algo_reverse__invalid_range2(void** state);
void test_algo_reverse__invalid_range3(void** state);
void test_algo_reverse__empty(void** state);
void test_algo_reverse__one(void** state);
void test_algo_reverse__reverse(void** state);
/*
 * test algo_reverse_copy
 */
UT_CASE_DECLARATION(algo_reverse_copy)
void test_algo_reverse_copy__invalid_range(void** state);
void test_algo_reverse_copy__invalid_range2(void** state);
void test_algo_reverse_copy__invalid_range3(void** state);
void test_algo_reverse_copy__invalid_dest_range(void** state);
void test_algo_reverse_copy__not_same_type(void** state);
void test_algo_reverse_copy__empty(void** state);
void test_algo_reverse_copy__one(void** state);
void test_algo_reverse_copy__reverse_copy(void** state);

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
    UT_CASE(test_algo_transform__user_define),\
    UT_CASE_BEGIN(algo_transform_binary, test_algo_transform_binary__invalid_first_range),\
    UT_CASE(test_algo_transform_binary__invalid_first_range2),\
    UT_CASE(test_algo_transform_binary__invalid_first_range3),\
    UT_CASE(test_algo_transform_binary__invalid_second_range),\
    UT_CASE(test_algo_transform_binary__invalid_dest_range),\
    UT_CASE(test_algo_transform_binary__invalid_range_not_same_type),\
    UT_CASE(test_algo_transform_binary__invalid_range_not_same_type2),\
    UT_CASE(test_algo_transform_binary__first_range_empty),\
    UT_CASE(test_algo_transform_binary__bfun_NULL),\
    UT_CASE(test_algo_transform_binary__c_builtin),\
    UT_CASE(test_algo_transform_binary__cstr),\
    UT_CASE(test_algo_transform_binary__cstl_builtin),\
    UT_CASE(test_algo_transform_binary__user_define),\
    UT_CASE_BEGIN(algo_replace, test_algo_replace__invalid_range),\
    UT_CASE(test_algo_replace__invalid_range2),\
    UT_CASE(test_algo_replace__invalid_range3),\
    UT_CASE(test_algo_replace__c_builtin),\
    UT_CASE(test_algo_replace__cstr),\
    UT_CASE(test_algo_replace__cstl_builtin),\
    UT_CASE(test_algo_replace__user_define),\
    UT_CASE_BEGIN(algo_replace_copy, test_algo_replace_copy__invalid_source_range),\
    UT_CASE(test_algo_replace_copy__invalid_source_range2),\
    UT_CASE(test_algo_replace_copy__invalid_source_range3),\
    UT_CASE(test_algo_replace_copy__invalid_dest_range),\
    UT_CASE(test_algo_replace_copy__invalid_range_not_same_type),\
    UT_CASE(test_algo_replace_copy__source_range_empty),\
    UT_CASE(test_algo_replace_copy__c_builtin),\
    UT_CASE(test_algo_replace_copy__cstr),\
    UT_CASE(test_algo_replace_copy__cstl_builtin),\
    UT_CASE(test_algo_replace_copy__user_define),\
    UT_CASE_BEGIN(algo_generate, test_algo_generate__invalid_range),\
    UT_CASE(test_algo_generate__invalid_range2),\
    UT_CASE(test_algo_generate__invalid_range3),\
    UT_CASE(test_algo_generate__range_empty),\
    UT_CASE(test_algo_generate__ufun_NULL),\
    UT_CASE(test_algo_generate__c_builtin),\
    UT_CASE(test_algo_generate__cstr),\
    UT_CASE(test_algo_generate__cstl_builtin),\
    UT_CASE(test_algo_generate__user_define),\
    UT_CASE_BEGIN(algo_generate_n, test_algo_generate_n__invalid_range),\
    UT_CASE(test_algo_generate_n__empty),\
    UT_CASE(test_algo_generate_n__ufun_NULL),\
    UT_CASE(test_algo_generate_n__c_builtin),\
    UT_CASE(test_algo_generate_n__cstr),\
    UT_CASE(test_algo_generate_n__cstl_builtin),\
    UT_CASE(test_algo_generate_n__user_define),\
    UT_CASE_BEGIN(algo_remove_if, test_algo_remove_if__invalid_range),\
    UT_CASE(test_algo_remove_if__invalid_range2),\
    UT_CASE(test_algo_remove_if__invalid_range3),\
    UT_CASE(test_algo_remove_if__empty),\
    UT_CASE(test_algo_remove_if__ufun_NULL),\
    UT_CASE(test_algo_remove_if__c_builtin),\
    UT_CASE(test_algo_remove_if__cstr),\
    UT_CASE(test_algo_remove_if__cstl_builtin),\
    UT_CASE(test_algo_remove_if__user_define),\
    UT_CASE_BEGIN(algo_remove_copy_if, test_algo_remove_copy_if__invalid_source_range),\
    UT_CASE(test_algo_remove_copy_if__invalid_source_range2),\
    UT_CASE(test_algo_remove_copy_if__invalid_source_range3),\
    UT_CASE(test_algo_remove_copy_if__invalid_dest_range),\
    UT_CASE(test_algo_remove_copy_if__invalid_range_not_same_type),\
    UT_CASE(test_algo_remove_copy_if__source_range_empty),\
    UT_CASE(test_algo_remove_copy_if__ufun_NULL),\
    UT_CASE(test_algo_remove_copy_if__c_builtin),\
    UT_CASE(test_algo_remove_copy_if__cstr),\
    UT_CASE(test_algo_remove_copy_if__cstl_builtin),\
    UT_CASE(test_algo_remove_copy_if__user_define),\
    UT_CASE_BEGIN(algo_unique, test_algo_unique__invalid_range),\
    UT_CASE(test_algo_unique__invalid_range2),\
    UT_CASE(test_algo_unique__invalid_range3),\
    UT_CASE(test_algo_unique__empty),\
    UT_CASE(test_algo_unique__no_duplication),\
    UT_CASE(test_algo_unique__c_builtin),\
    UT_CASE(test_algo_unique__cstr),\
    UT_CASE(test_algo_unique__cstl_builtin),\
    UT_CASE(test_algo_unique__user_define),\
    UT_CASE_BEGIN(algo_unique_if, test_algo_unique_if__invalid_range),\
    UT_CASE(test_algo_unique_if__invalid_range2),\
    UT_CASE(test_algo_unique_if__invalid_range3),\
    UT_CASE(test_algo_unique_if__empty),\
    UT_CASE(test_algo_unique_if__bfun_NULL),\
    UT_CASE(test_algo_unique_if__c_builtin),\
    UT_CASE(test_algo_unique_if__cstr),\
    UT_CASE(test_algo_unique_if__cstl_builtin),\
    UT_CASE(test_algo_unique_if__user_define),\
    UT_CASE_BEGIN(algo_unique_copy, test_algo_unique_copy__invalid_range),\
    UT_CASE(test_algo_unique_copy__invalid_range2),\
    UT_CASE(test_algo_unique_copy__invalid_range3),\
    UT_CASE(test_algo_unique_copy__invalid_dest_range),\
    UT_CASE(test_algo_unique_copy__not_same_type),\
    UT_CASE(test_algo_unique_copy__empty),\
    UT_CASE(test_algo_unique_copy__no_duplication),\
    UT_CASE(test_algo_unique_copy__c_builtin),\
    UT_CASE(test_algo_unique_copy__cstr),\
    UT_CASE(test_algo_unique_copy__cstl_builtin),\
    UT_CASE(test_algo_unique_copy__user_define),\
    UT_CASE_BEGIN(algo_unique_copy_if, test_algo_unique_copy_if__invalid_range),\
    UT_CASE(test_algo_unique_copy_if__invalid_range2),\
    UT_CASE(test_algo_unique_copy_if__invalid_range3),\
    UT_CASE(test_algo_unique_copy_if__invalid_dest_range),\
    UT_CASE(test_algo_unique_copy_if__not_same_type),\
    UT_CASE(test_algo_unique_copy_if__empty),\
    UT_CASE(test_algo_unique_copy_if__bfun_NULL),\
    UT_CASE(test_algo_unique_copy_if__c_builtin),\
    UT_CASE(test_algo_unique_copy_if__cstr),\
    UT_CASE(test_algo_unique_copy_if__cstl_builtin),\
    UT_CASE(test_algo_unique_copy_if__user_define),\
    UT_CASE_BEGIN(algo_reverse, test_algo_reverse__invalid_range),\
    UT_CASE(test_algo_reverse__invalid_range2),\
    UT_CASE(test_algo_reverse__invalid_range3),\
    UT_CASE(test_algo_reverse__empty),\
    UT_CASE(test_algo_reverse__one),\
    UT_CASE(test_algo_reverse__reverse),\
    UT_CASE_BEGIN(algo_reverse_copy, test_algo_reverse_copy__invalid_range),\
    UT_CASE(test_algo_reverse_copy__invalid_range2),\
    UT_CASE(test_algo_reverse_copy__invalid_range3),\
    UT_CASE(test_algo_reverse_copy__invalid_dest_range),\
    UT_CASE(test_algo_reverse_copy__not_same_type),\
    UT_CASE(test_algo_reverse_copy__empty),\
    UT_CASE(test_algo_reverse_copy__one),\
    UT_CASE(test_algo_reverse_copy__reverse_copy)

#endif /* _UT_CSTL_ALGO_MUTATING_H_ */

