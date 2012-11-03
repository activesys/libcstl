#ifndef _UT_CSTL_ALGO_SORTING_H_
#define _UT_CSTL_ALGO_SORTING_H_

UT_SUIT_DECLARATION(cstl_algo_sorting)

/*
 * test algo_is_sorted
 */
UT_CASE_DECLARATION(algo_is_sorted)
void test_algo_is_sorted__invalid_range(void** state);
void test_algo_is_sorted__invalid_range2(void** state);
void test_algo_is_sorted__invalid_range3(void** state);
void test_algo_is_sorted__empty(void** state);
void test_algo_is_sorted__one(void** state);
void test_algo_is_sorted__true(void** state);
void test_algo_is_sorted__false(void** state);
void test_algo_is_sorted__all_equal(void** state);
/*
 * test algo_is_sorted_if
 */
UT_CASE_DECLARATION(algo_is_sorted_if)
void test_algo_is_sorted_if__invalid_range(void** state);
void test_algo_is_sorted_if__invalid_range2(void** state);
void test_algo_is_sorted_if__invalid_range3(void** state);
void test_algo_is_sorted_if__empty(void** state);
void test_algo_is_sorted_if__one(void** state);
void test_algo_is_sorted_if__bfun_NULL_true(void** state);
void test_algo_is_sorted_if__bfun_NULL_false(void** state);
void test_algo_is_sorted_if__bfun_NULL_all_equal(void** state);
void test_algo_is_sorted_if__true(void** state);
void test_algo_is_sorted_if__false(void** state);
void test_algo_is_sorted_if__all_equal(void** state);
/*
 * test algo_partial_sort
 */
UT_CASE_DECLARATION(algo_partial_sort)
void test_algo_partial_sort__invalid_range(void** state);
void test_algo_partial_sort__invalid_range2(void** state);
void test_algo_partial_sort__invalid_range3(void** state);
void test_algo_partial_sort__empty(void** state);
void test_algo_partial_sort__first_range_empty(void** state);
void test_algo_partial_sort__normal(void** state);
void test_algo_partial_sort__second_range_empty(void** state);
/*
 * test algo_partial_sort_if
 */
UT_CASE_DECLARATION(algo_partial_sort_if)
void test_algo_partial_sort_if__invalid_range(void** state);
void test_algo_partial_sort_if__invalid_range2(void** state);
void test_algo_partial_sort_if__invalid_range3(void** state);
void test_algo_partial_sort_if__empty(void** state);
void test_algo_partial_sort_if__bfun_NULL_first_range_empty(void** state);
void test_algo_partial_sort_if__bfun_NULL_normal(void** state);
void test_algo_partial_sort_if__bfun_NULL_second_range_empty(void** state);
void test_algo_partial_sort_if__first_range_empty(void** state);
void test_algo_partial_sort_if__normal(void** state);
void test_algo_partial_sort_if__second_range_empty(void** state);
/*
 * test algo_partial_sort_copy
 */
UT_CASE_DECLARATION(algo_partial_sort_copy)
void test_algo_partial_sort_copy__invalid_first_range(void** state);
void test_algo_partial_sort_copy__invalid_first_range2(void** state);
void test_algo_partial_sort_copy__invalid_first_range3(void** state);
void test_algo_partial_sort_copy__invalid_second_range(void** state);
void test_algo_partial_sort_copy__invalid_second_range2(void** state);
void test_algo_partial_sort_copy__invalid_second_range3(void** state);
void test_algo_partial_sort_copy__not_same_type(void** state);
void test_algo_partial_sort_copy__first_range_empty(void** state);
void test_algo_partial_sort_copy__second_range_emtpy(void** state);
void test_algo_partial_sort_copy__all_empty(void** state);
void test_algo_partial_sort_copy__first_less_second(void** state);
void test_algo_partial_sort_copy__first_equal_second(void** state);
void test_algo_partial_sort_copy__first_greater_second(void** state);
/*
 * test algo_partial_sort_copy_if
 */
UT_CASE_DECLARATION(algo_partial_sort_copy_if)
void test_algo_partial_sort_copy_if__invalid_first_range(void** state);
void test_algo_partial_sort_copy_if__invalid_first_range2(void** state);
void test_algo_partial_sort_copy_if__invalid_first_range3(void** state);
void test_algo_partial_sort_copy_if__invalid_second_range(void** state);
void test_algo_partial_sort_copy_if__invalid_second_range2(void** state);
void test_algo_partial_sort_copy_if__invalid_second_range3(void** state);
void test_algo_partial_sort_copy_if__not_same_type(void** state);
void test_algo_partial_sort_copy_if__first_range_empty(void** state);
void test_algo_partial_sort_copy_if__second_range_emtpy(void** state);
void test_algo_partial_sort_copy_if__all_empty(void** state);
void test_algo_partial_sort_copy_if__bfun_NULL_first_less_second(void** state);
void test_algo_partial_sort_copy_if__bfun_NULL_first_equal_second(void** state);
void test_algo_partial_sort_copy_if__bfun_NULL_first_greater_second(void** state);
void test_algo_partial_sort_copy_if__first_less_second(void** state);
void test_algo_partial_sort_copy_if__first_equal_second(void** state);
void test_algo_partial_sort_copy_if__first_greater_second(void** state);
/*
 * test algo_sort
 */
UT_CASE_DECLARATION(algo_sort)
void test_algo_sort__invalid_range(void** state);
void test_algo_sort__invalid_range2(void** state);
void test_algo_sort__invalid_range3(void** state);
void test_algo_sort__empty(void** state);
void test_algo_sort__less_than_threshold(void** state);
void test_algo_sort__more_than_threshold(void** state);
/*
 * test algo_sort_if
 */
UT_CASE_DECLARATION(algo_sort_if)
void test_algo_sort_if__invalid_range(void** state);
void test_algo_sort_if__invalid_range2(void** state);
void test_algo_sort_if__invalid_range3(void** state);
void test_algo_sort_if__empty(void** state);
void test_algo_sort_if__bfun_NULL_less_than_threshold(void** state);
void test_algo_sort_if__bfun_NULL_more_than_threshold(void** state);
void test_algo_sort_if__less_than_threshold(void** state);
void test_algo_sort_if__more_than_threshold(void** state);
/*
 * test algo_merge
 */
UT_CASE_DECLARATION(algo_merge)
void test_algo_merge__invalid_first_range(void** state);
void test_algo_merge__invalid_second_range(void** state);
void test_algo_merge__invalid_third_range(void** state);
void test_algo_merge__first_not_same_type(void** state);
void test_algo_merge__second_not_same_type(void** state);
void test_algo_merge__third_not_same_type(void** state);
void test_algo_merge__first_empty(void** state);
void test_algo_merge__second_empty(void** state);
void test_algo_merge__all_empty(void** state);
void test_algo_merge__first_lead_second(void** state);
void test_algo_merge__second_lead_first(void** state);
void test_algo_merge__overlap_first_lead_second(void** state);
void test_algo_merge__overlap_second_lead_first(void** state);
void test_algo_merge__overlap(void** state);
/*
 * test algo_merge_if
 */
UT_CASE_DECLARATION(algo_merge_if)
void test_algo_merge_if__invalid_first_range(void** state);
void test_algo_merge_if__invalid_second_range(void** state);
void test_algo_merge_if__invalid_third_range(void** state);
void test_algo_merge_if__first_not_same_type(void** state);
void test_algo_merge_if__second_not_same_type(void** state);
void test_algo_merge_if__third_not_same_type(void** state);
void test_algo_merge_if__bfun_NULL_first_empty(void** state);
void test_algo_merge_if__bfun_NULL_second_empty(void** state);
void test_algo_merge_if__bfun_NULL_all_empty(void** state);
void test_algo_merge_if__bfun_NULL_first_lead_second(void** state);
void test_algo_merge_if__bfun_NULL_second_lead_first(void** state);
void test_algo_merge_if__bfun_NULL_overlap_first_lead_second(void** state);
void test_algo_merge_if__bfun_NULL_overlap_second_lead_first(void** state);
void test_algo_merge_if__bfun_NULL_overlap(void** state);
void test_algo_merge_if__first_empty(void** state);
void test_algo_merge_if__second_empty(void** state);
void test_algo_merge_if__all_empty(void** state);
void test_algo_merge_if__first_lead_second(void** state);
void test_algo_merge_if__second_lead_first(void** state);
void test_algo_merge_if__overlap_first_lead_second(void** state);
void test_algo_merge_if__overlap_second_lead_first(void** state);
void test_algo_merge_if__overlap(void** state);
/*
 * test algo_inplace_merge
 */
UT_CASE_DECLARATION(algo_inplace_merge)
void test_algo_inplace_merge__invalid_first_range(void** state);
void test_algo_inplace_merge__invalid_second_range(void** state);
void test_algo_inplace_merge__invalid_range(void** state);
void test_algo_inplace_merge__empty(void** state);
void test_algo_inplace_merge__first_empty(void** state);
void test_algo_inplace_merge__second_empty(void** state);
void test_algo_inplace_merge__first_lead_second(void** state);
void test_algo_inplace_merge__second_lead_first(void** state);
void test_algo_inplace_merge__overlap_first_lead_second(void** state);
void test_algo_inplace_merge__overlap_second_lead_first(void** state);
void test_algo_inplace_merge__overlap(void** state);
void test_algo_inplace_merge__cstr(void** state);
void test_algo_inplace_merge__cstl_builtin(void** state);
void test_algo_inplace_merge__user_define(void** state);
/*
 * test algo_inplace_merge_if
 */
UT_CASE_DECLARATION(algo_inplace_merge_if)
void test_algo_inplace_merge_if__invalid_first_range(void** state);
void test_algo_inplace_merge_if__invalid_second_range(void** state);
void test_algo_inplace_merge_if__invalid_range(void** state);
void test_algo_inplace_merge_if__empty(void** state);
void test_algo_inplace_merge_if__first_empty(void** state);
void test_algo_inplace_merge_if__second_empty(void** state);
void test_algo_inplace_merge_if__bfun_NULL_first_lead_second(void** state);
void test_algo_inplace_merge_if__bfun_NULL_second_lead_first(void** state);
void test_algo_inplace_merge_if__bfun_NULL_overlap_first_lead_second(void** state);
void test_algo_inplace_merge_if__bfun_NULL_overlap_second_lead_first(void** state);
void test_algo_inplace_merge_if__bfun_NULL_overlap(void** state);
void test_algo_inplace_merge_if__bfun_NULL_cstr(void** state);
void test_algo_inplace_merge_if__bfun_NULL_cstl_builtin(void** state);
void test_algo_inplace_merge_if__bfun_NULL_user_define(void** state);
void test_algo_inplace_merge_if__first_lead_second(void** state);
void test_algo_inplace_merge_if__second_lead_first(void** state);
void test_algo_inplace_merge_if__overlap_first_lead_second(void** state);
void test_algo_inplace_merge_if__overlap_second_lead_first(void** state);
void test_algo_inplace_merge_if__overlap(void** state);
void test_algo_inplace_merge_if__cstr(void** state);
void test_algo_inplace_merge_if__cstl_builtin(void** state);
void test_algo_inplace_merge_if__user_define(void** state);
/*
 * test algo_stable_sort
 */
UT_CASE_DECLARATION(algo_stable_sort)
void test_algo_stable_sort__invalid_range(void** state);
void test_algo_stable_sort__invalid_range2(void** state);
void test_algo_stable_sort__invalid_range3(void** state);
void test_algo_stable_sort__empty(void** state);
void test_algo_stable_sort__one(void** state);
void test_algo_stable_sort__less_than_threshold(void** state);
void test_algo_stable_sort__more_than_threshold(void** state);
/*
 * test algo_stable_sort_if
 */
UT_CASE_DECLARATION(algo_stable_sort_if)
void test_algo_stable_sort_if__invalid_range(void** state);
void test_algo_stable_sort_if__invalid_range2(void** state);
void test_algo_stable_sort_if__invalid_range3(void** state);
void test_algo_stable_sort_if__empty(void** state);
void test_algo_stable_sort_if__one(void** state);
void test_algo_stable_sort_if__bfun_NULL_less_than_threshold(void** state);
void test_algo_stable_sort_if__bfun_NULL_more_than_threshold(void** state);
void test_algo_stable_sort_if__less_than_threshold(void** state);
void test_algo_stable_sort_if__more_than_threshold(void** state);

#define UT_CSTL_ALGO_SORTING_CASE\
    UT_SUIT_BEGIN(cstl_algo_sorting, test_algo_is_sorted__invalid_range),\
    UT_CASE(test_algo_is_sorted__invalid_range2),\
    UT_CASE(test_algo_is_sorted__invalid_range3),\
    UT_CASE(test_algo_is_sorted__empty),\
    UT_CASE(test_algo_is_sorted__one),\
    UT_CASE(test_algo_is_sorted__true),\
    UT_CASE(test_algo_is_sorted__false),\
    UT_CASE(test_algo_is_sorted__all_equal),\
    UT_CASE_BEGIN(algo_is_sorted_if, test_algo_is_sorted_if__invalid_range),\
    UT_CASE(test_algo_is_sorted_if__invalid_range2),\
    UT_CASE(test_algo_is_sorted_if__invalid_range3),\
    UT_CASE(test_algo_is_sorted_if__empty),\
    UT_CASE(test_algo_is_sorted_if__one),\
    UT_CASE(test_algo_is_sorted_if__bfun_NULL_true),\
    UT_CASE(test_algo_is_sorted_if__bfun_NULL_false),\
    UT_CASE(test_algo_is_sorted_if__bfun_NULL_all_equal),\
    UT_CASE(test_algo_is_sorted_if__true),\
    UT_CASE(test_algo_is_sorted_if__false),\
    UT_CASE(test_algo_is_sorted_if__all_equal),\
    UT_CASE_BEGIN(algo_partial_sort, test_algo_partial_sort__invalid_range),\
    UT_CASE(test_algo_partial_sort__invalid_range2),\
    UT_CASE(test_algo_partial_sort__invalid_range3),\
    UT_CASE(test_algo_partial_sort__empty),\
    UT_CASE(test_algo_partial_sort__first_range_empty),\
    UT_CASE(test_algo_partial_sort__normal),\
    UT_CASE(test_algo_partial_sort__second_range_empty),\
    UT_CASE_BEGIN(algo_partial_sort_if, test_algo_partial_sort_if__invalid_range),\
    UT_CASE(test_algo_partial_sort_if__invalid_range2),\
    UT_CASE(test_algo_partial_sort_if__invalid_range3),\
    UT_CASE(test_algo_partial_sort_if__empty),\
    UT_CASE(test_algo_partial_sort_if__bfun_NULL_first_range_empty),\
    UT_CASE(test_algo_partial_sort_if__bfun_NULL_normal),\
    UT_CASE(test_algo_partial_sort_if__bfun_NULL_second_range_empty),\
    UT_CASE(test_algo_partial_sort_if__first_range_empty),\
    UT_CASE(test_algo_partial_sort_if__normal),\
    UT_CASE(test_algo_partial_sort_if__second_range_empty),\
    UT_CASE_BEGIN(algo_partial_sort_copy, test_algo_partial_sort_copy__invalid_first_range),\
    UT_CASE(test_algo_partial_sort_copy__invalid_first_range2),\
    UT_CASE(test_algo_partial_sort_copy__invalid_first_range3),\
    UT_CASE(test_algo_partial_sort_copy__invalid_second_range),\
    UT_CASE(test_algo_partial_sort_copy__invalid_second_range2),\
    UT_CASE(test_algo_partial_sort_copy__invalid_second_range3),\
    UT_CASE(test_algo_partial_sort_copy__not_same_type),\
    UT_CASE(test_algo_partial_sort_copy__first_range_empty),\
    UT_CASE(test_algo_partial_sort_copy__second_range_emtpy),\
    UT_CASE(test_algo_partial_sort_copy__all_empty),\
    UT_CASE(test_algo_partial_sort_copy__first_less_second),\
    UT_CASE(test_algo_partial_sort_copy__first_equal_second),\
    UT_CASE(test_algo_partial_sort_copy__first_greater_second),\
    UT_CASE_BEGIN(algo_partial_sort_copy_if, test_algo_partial_sort_copy_if__invalid_first_range),\
    UT_CASE(test_algo_partial_sort_copy_if__invalid_first_range2),\
    UT_CASE(test_algo_partial_sort_copy_if__invalid_first_range3),\
    UT_CASE(test_algo_partial_sort_copy_if__invalid_second_range),\
    UT_CASE(test_algo_partial_sort_copy_if__invalid_second_range2),\
    UT_CASE(test_algo_partial_sort_copy_if__invalid_second_range3),\
    UT_CASE(test_algo_partial_sort_copy_if__not_same_type),\
    UT_CASE(test_algo_partial_sort_copy_if__first_range_empty),\
    UT_CASE(test_algo_partial_sort_copy_if__second_range_emtpy),\
    UT_CASE(test_algo_partial_sort_copy_if__all_empty),\
    UT_CASE(test_algo_partial_sort_copy_if__bfun_NULL_first_less_second),\
    UT_CASE(test_algo_partial_sort_copy_if__bfun_NULL_first_equal_second),\
    UT_CASE(test_algo_partial_sort_copy_if__bfun_NULL_first_greater_second),\
    UT_CASE(test_algo_partial_sort_copy_if__first_less_second),\
    UT_CASE(test_algo_partial_sort_copy_if__first_equal_second),\
    UT_CASE(test_algo_partial_sort_copy_if__first_greater_second),\
    UT_CASE_BEGIN(algo_sort, test_algo_sort__invalid_range),\
    UT_CASE(test_algo_sort__invalid_range2),\
    UT_CASE(test_algo_sort__invalid_range3),\
    UT_CASE(test_algo_sort__empty),\
    UT_CASE(test_algo_sort__less_than_threshold),\
    UT_CASE(test_algo_sort__more_than_threshold),\
    UT_CASE_BEGIN(algo_sort_if, test_algo_sort_if__invalid_range),\
    UT_CASE(test_algo_sort_if__invalid_range2),\
    UT_CASE(test_algo_sort_if__invalid_range3),\
    UT_CASE(test_algo_sort_if__empty),\
    UT_CASE(test_algo_sort_if__bfun_NULL_less_than_threshold),\
    UT_CASE(test_algo_sort_if__bfun_NULL_more_than_threshold),\
    UT_CASE(test_algo_sort_if__less_than_threshold),\
    UT_CASE(test_algo_sort_if__more_than_threshold),\
    UT_CASE_BEGIN(algo_merge, test_algo_merge__invalid_first_range),\
    UT_CASE(test_algo_merge__invalid_second_range),\
    UT_CASE(test_algo_merge__invalid_third_range),\
    UT_CASE(test_algo_merge__first_not_same_type),\
    UT_CASE(test_algo_merge__second_not_same_type),\
    UT_CASE(test_algo_merge__third_not_same_type),\
    UT_CASE(test_algo_merge__first_empty),\
    UT_CASE(test_algo_merge__second_empty),\
    UT_CASE(test_algo_merge__all_empty),\
    UT_CASE(test_algo_merge__first_lead_second),\
    UT_CASE(test_algo_merge__second_lead_first),\
    UT_CASE(test_algo_merge__overlap_first_lead_second),\
    UT_CASE(test_algo_merge__overlap_second_lead_first),\
    UT_CASE(test_algo_merge__overlap),\
    UT_CASE_BEGIN(algo_merge_if, test_algo_merge_if__invalid_first_range),\
    UT_CASE(test_algo_merge_if__invalid_second_range),\
    UT_CASE(test_algo_merge_if__invalid_third_range),\
    UT_CASE(test_algo_merge_if__first_not_same_type),\
    UT_CASE(test_algo_merge_if__second_not_same_type),\
    UT_CASE(test_algo_merge_if__third_not_same_type),\
    UT_CASE(test_algo_merge_if__bfun_NULL_first_empty),\
    UT_CASE(test_algo_merge_if__bfun_NULL_second_empty),\
    UT_CASE(test_algo_merge_if__bfun_NULL_all_empty),\
    UT_CASE(test_algo_merge_if__bfun_NULL_first_lead_second),\
    UT_CASE(test_algo_merge_if__bfun_NULL_second_lead_first),\
    UT_CASE(test_algo_merge_if__bfun_NULL_overlap_first_lead_second),\
    UT_CASE(test_algo_merge_if__bfun_NULL_overlap_second_lead_first),\
    UT_CASE(test_algo_merge_if__bfun_NULL_overlap),\
    UT_CASE(test_algo_merge_if__first_empty),\
    UT_CASE(test_algo_merge_if__second_empty),\
    UT_CASE(test_algo_merge_if__all_empty),\
    UT_CASE(test_algo_merge_if__first_lead_second),\
    UT_CASE(test_algo_merge_if__second_lead_first),\
    UT_CASE(test_algo_merge_if__overlap_first_lead_second),\
    UT_CASE(test_algo_merge_if__overlap_second_lead_first),\
    UT_CASE(test_algo_merge_if__overlap),\
    UT_CASE_BEGIN(algo_inplace_merge, test_algo_inplace_merge__invalid_first_range),\
    UT_CASE(test_algo_inplace_merge__invalid_second_range),\
    UT_CASE(test_algo_inplace_merge__invalid_range),\
    UT_CASE(test_algo_inplace_merge__empty),\
    UT_CASE(test_algo_inplace_merge__first_empty),\
    UT_CASE(test_algo_inplace_merge__second_empty),\
    UT_CASE(test_algo_inplace_merge__first_lead_second),\
    UT_CASE(test_algo_inplace_merge__second_lead_first),\
    UT_CASE(test_algo_inplace_merge__overlap_first_lead_second),\
    UT_CASE(test_algo_inplace_merge__overlap_second_lead_first),\
    UT_CASE(test_algo_inplace_merge__overlap),\
    UT_CASE(test_algo_inplace_merge__cstr),\
    UT_CASE(test_algo_inplace_merge__cstl_builtin),\
    UT_CASE(test_algo_inplace_merge__user_define),\
    UT_CASE_BEGIN(algo_inplace_merge_if, test_algo_inplace_merge_if__invalid_first_range),\
    UT_CASE(test_algo_inplace_merge_if__invalid_second_range),\
    UT_CASE(test_algo_inplace_merge_if__invalid_range),\
    UT_CASE(test_algo_inplace_merge_if__empty),\
    UT_CASE(test_algo_inplace_merge_if__first_empty),\
    UT_CASE(test_algo_inplace_merge_if__second_empty),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_first_lead_second),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_second_lead_first),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_overlap_first_lead_second),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_overlap_second_lead_first),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_overlap),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_cstr),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_cstl_builtin),\
    UT_CASE(test_algo_inplace_merge_if__bfun_NULL_user_define),\
    UT_CASE(test_algo_inplace_merge_if__first_lead_second),\
    UT_CASE(test_algo_inplace_merge_if__second_lead_first),\
    UT_CASE(test_algo_inplace_merge_if__overlap_first_lead_second),\
    UT_CASE(test_algo_inplace_merge_if__overlap_second_lead_first),\
    UT_CASE(test_algo_inplace_merge_if__overlap),\
    UT_CASE(test_algo_inplace_merge_if__cstr),\
    UT_CASE(test_algo_inplace_merge_if__cstl_builtin),\
    UT_CASE(test_algo_inplace_merge_if__user_define),\
    UT_CASE_BEGIN(algo_stable_sort, test_algo_stable_sort__invalid_range),\
    UT_CASE(test_algo_stable_sort__invalid_range2),\
    UT_CASE(test_algo_stable_sort__invalid_range3),\
    UT_CASE(test_algo_stable_sort__empty),\
    UT_CASE(test_algo_stable_sort__one),\
    UT_CASE(test_algo_stable_sort__less_than_threshold),\
    UT_CASE(test_algo_stable_sort__more_than_threshold),\
    UT_CASE_BEGIN(algo_stable_sort_if, test_algo_stable_sort_if__invalid_range),\
    UT_CASE(test_algo_stable_sort_if__invalid_range2),\
    UT_CASE(test_algo_stable_sort_if__invalid_range3),\
    UT_CASE(test_algo_stable_sort_if__empty),\
    UT_CASE(test_algo_stable_sort_if__one),\
    UT_CASE(test_algo_stable_sort_if__bfun_NULL_less_than_threshold),\
    UT_CASE(test_algo_stable_sort_if__bfun_NULL_more_than_threshold),\
    UT_CASE(test_algo_stable_sort_if__less_than_threshold),\
    UT_CASE(test_algo_stable_sort_if__more_than_threshold)

#endif /* _UT_CSTL_ALGO_SORTING_H_ */

