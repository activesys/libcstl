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
/*
 * test algo_nth_element
 */
UT_CASE_DECLARATION(algo_nth_element)
void test_algo_nth_element__invalid_first_range(void** state);
void test_algo_nth_element__invalid_second_range(void** state);
void test_algo_nth_element__invalid_range(void** state);
void test_algo_nth_element__empty(void** state);
void test_algo_nth_element__three(void** state);
void test_algo_nth_element__first_element(void** state);
void test_algo_nth_element__last_element(void** state);
void test_algo_nth_element__normal(void** state);
void test_algo_nth_element__last(void** state);
/*
 * test algo_nth_element_if
 */
UT_CASE_DECLARATION(algo_nth_element_if)
void test_algo_nth_element_if__invalid_first_range(void** state);
void test_algo_nth_element_if__invalid_second_range(void** state);
void test_algo_nth_element_if__invalid_range(void** state);
void test_algo_nth_element_if__empty(void** state);
void test_algo_nth_element_if__three(void** state);
void test_algo_nth_element_if__first_element(void** state);
void test_algo_nth_element_if__last_element(void** state);
void test_algo_nth_element_if__normal(void** state);
void test_algo_nth_element_if__last(void** state);
void test_algo_nth_element_if__bfun_NULL_first_element(void** state);
void test_algo_nth_element_if__bfun_NULL_last_element(void** state);
void test_algo_nth_element_if__bfun_NULL_normal(void** state);
void test_algo_nth_element_if__bfun_NULL_last(void** state);
/*
 * test algo_includes
 */
UT_CASE_DECLARATION(algo_includes)
void test_algo_includes__invalid_first_range(void** state);
void test_algo_includes__invalid_second_range(void** state);
void test_algo_includes__not_same_type(void** state);
void test_algo_includes__first_empty(void** state);
void test_algo_includes__second_empty(void** state);
void test_algo_includes__all_empty(void** state);
void test_algo_includes__true(void** state);
void test_algo_includes__false(void** state);
/*
 * test algo_includes_if
 */
UT_CASE_DECLARATION(algo_includes_if)
void test_algo_includes_if__invalid_first_range(void** state);
void test_algo_includes_if__invalid_second_range(void** state);
void test_algo_includes_if__not_same_type(void** state);
void test_algo_includes_if__first_empty(void** state);
void test_algo_includes_if__second_empty(void** state);
void test_algo_includes_if__all_empty(void** state);
void test_algo_includes_if__bfun_NULL_true(void** state);
void test_algo_includes_if__bfun_NULL_false(void** state);
void test_algo_includes_if__true(void** state);
void test_algo_includes_if__false(void** state);
/*
 * test algo_set_union
 */
UT_CASE_DECLARATION(algo_set_union)
void test_algo_set_union__invalid_first_range(void** state);
void test_algo_set_union__invalid_second_range(void** state);
void test_algo_set_union__invalid_third_range(void** state);
void test_algo_set_union__first_not_same_type(void** state);
void test_algo_set_union__second_not_same_type(void** state);
void test_algo_set_union__third_not_same_type(void** state);
void test_algo_set_union__first_empty(void** state);
void test_algo_set_union__second_empty(void** state);
void test_algo_set_union__all_empty(void** state);
void test_algo_set_union__first_lead_second(void** state);
void test_algo_set_union__first_overlap_second(void** state);
void test_algo_set_union__second_overlap_first(void** state);
void test_algo_set_union__second_lead_first(void** state);
/*
 * test algo_set_union_if
 */
UT_CASE_DECLARATION(algo_set_union_if)
void test_algo_set_union_if__invalid_first_range(void** state);
void test_algo_set_union_if__invalid_second_range(void** state);
void test_algo_set_union_if__invalid_third_range(void** state);
void test_algo_set_union_if__first_not_same_type(void** state);
void test_algo_set_union_if__second_not_same_type(void** state);
void test_algo_set_union_if__third_not_same_type(void** state);
void test_algo_set_union_if__bfun_NULL_first_lead_second(void** state);
void test_algo_set_union_if__bfun_NULL_first_overlap_second(void** state);
void test_algo_set_union_if__bfun_NULL_second_overlap_first(void** state);
void test_algo_set_union_if__bfun_NULL_second_lead_first(void** state);
void test_algo_set_union_if__first_lead_second(void** state);
void test_algo_set_union_if__first_overlap_second(void** state);
void test_algo_set_union_if__second_overlap_first(void** state);
void test_algo_set_union_if__second_lead_first(void** state);
/*
 * test algo_set_intersection
 */
UT_CASE_DECLARATION(algo_set_intersection)
void test_algo_set_intersection__invalid_first_range(void** state);
void test_algo_set_intersection__invalid_second_range(void** state);
void test_algo_set_intersection__invalid_third_range(void** state);
void test_algo_set_intersection__first_not_same_type(void** state);
void test_algo_set_intersection__second_not_same_type(void** state);
void test_algo_set_intersection__third_not_same_type(void** state);
void test_algo_set_intersection__result_empty(void** state);
void test_algo_set_intersection__result_not_empty(void** state);
/*
 * test algo_set_intersection_if
 */
UT_CASE_DECLARATION(algo_set_intersection_if)
void test_algo_set_intersection_if__invalid_first_range(void** state);
void test_algo_set_intersection_if__invalid_second_range(void** state);
void test_algo_set_intersection_if__invalid_third_range(void** state);
void test_algo_set_intersection_if__first_not_same_type(void** state);
void test_algo_set_intersection_if__second_not_same_type(void** state);
void test_algo_set_intersection_if__third_not_same_type(void** state);
void test_algo_set_intersection_if__bfun_NULL_result_empty(void** state);
void test_algo_set_intersection_if__bfun_NULL_result_not_empty(void** state);
void test_algo_set_intersection_if__result_empty(void** state);
void test_algo_set_intersection_if__result_not_empty(void** state);
/*
 * test algo_set_difference
 */
UT_CASE_DECLARATION(algo_set_difference)
void test_algo_set_difference__invalid_first_range(void** state);
void test_algo_set_difference__invalid_second_range(void** state);
void test_algo_set_difference__invalid_third_range(void** state);
void test_algo_set_difference__first_not_same_type(void** state);
void test_algo_set_difference__second_not_same_type(void** state);
void test_algo_set_difference__third_not_same_type(void** state);
void test_algo_set_difference__result_difference(void** state);
void test_algo_set_difference__result_not_difference(void** state);
/*
 * test algo_set_difference_if
 */
UT_CASE_DECLARATION(algo_set_difference_if)
void test_algo_set_difference_if__invalid_first_range(void** state);
void test_algo_set_difference_if__invalid_second_range(void** state);
void test_algo_set_difference_if__invalid_third_range(void** state);
void test_algo_set_difference_if__first_not_same_type(void** state);
void test_algo_set_difference_if__second_not_same_type(void** state);
void test_algo_set_difference_if__third_not_same_type(void** state);
void test_algo_set_difference_if__bfun_NULL_result_difference(void** state);
void test_algo_set_difference_if__bfun_NULL_result_not_difference(void** state);
void test_algo_set_difference_if__result_difference(void** state);
void test_algo_set_difference_if__result_not_difference(void** state);
/*
 * test algo_set_symmetric_difference
 */
UT_CASE_DECLARATION(algo_set_symmetric_difference)
void test_algo_set_symmetric_difference__invalid_first_range(void** state);
void test_algo_set_symmetric_difference__invalid_second_range(void** state);
void test_algo_set_symmetric_difference__invalid_third_range(void** state);
void test_algo_set_symmetric_difference__first_not_same_type(void** state);
void test_algo_set_symmetric_difference__second_not_same_type(void** state);
void test_algo_set_symmetric_difference__third_not_same_type(void** state);
void test_algo_set_symmetric_difference__result_difference(void** state);
void test_algo_set_symmetric_difference__result_not_difference(void** state);
/*
 * test algo_set_symmetric_difference_if
 */
UT_CASE_DECLARATION(algo_set_symmetric_difference_if)
void test_algo_set_symmetric_difference_if__invalid_first_range(void** state);
void test_algo_set_symmetric_difference_if__invalid_second_range(void** state);
void test_algo_set_symmetric_difference_if__invalid_third_range(void** state);
void test_algo_set_symmetric_difference_if__first_not_same_type(void** state);
void test_algo_set_symmetric_difference_if__second_not_same_type(void** state);
void test_algo_set_symmetric_difference_if__third_not_same_type(void** state);
void test_algo_set_symmetric_difference_if__bfun_NULL_result_difference(void** state);
void test_algo_set_symmetric_difference_if__bfun_NULL_result_not_difference(void** state);
void test_algo_set_symmetric_difference_if__result_difference(void** state);
void test_algo_set_symmetric_difference_if__result_not_difference(void** state);
/*
 * test algo_max
 */
UT_CASE_DECLARATION(algo_max)
void test_algo_max__not_same_type(void** state);
void test_algo_max__first_max(void** state);
void test_algo_max__second_max(void** state);
void test_algo_max__equal(void** state);
/*
 * test algo_max_if
 */
UT_CASE_DECLARATION(algo_max_if)
void test_algo_max_if__not_same_type(void** state);
void test_algo_max_if__equal(void** state);
void test_algo_max_if__bfun_NULL_first_max(void** state);
void test_algo_max_if__bfun_NULL_second_max(void** state);
void test_algo_max_if__first_max(void** state);
void test_algo_max_if__second_max(void** state);
/*
 * test algo_min
 */
UT_CASE_DECLARATION(algo_min)
void test_algo_min__not_same_type(void** state);
void test_algo_min__first_min(void** state);
void test_algo_min__second_min(void** state);
void test_algo_min__equal(void** state);
/*
 * test algo_min_if
 */
UT_CASE_DECLARATION(algo_min_if)
void test_algo_min_if__not_same_type(void** state);
void test_algo_min_if__equal(void** state);
void test_algo_min_if__bfun_NULL_first_min(void** state);
void test_algo_min_if__bfun_NULL_second_min(void** state);
void test_algo_min_if__first_min(void** state);
void test_algo_min_if__second_min(void** state);
/*
 * test algo_max_element
 */
UT_CASE_DECLARATION(algo_max_element)
void test_algo_max_element__invalid_range(void** state);
void test_algo_max_element__invalid_range2(void** state);
void test_algo_max_element__invalid_range3(void** state);
void test_algo_max_element__empty(void** state);
void test_algo_max_element__normal(void** state);
void test_algo_max_element__equal(void** state);
/*
 * test algo_max_element_if
 */
UT_CASE_DECLARATION(algo_max_element_if)
void test_algo_max_element_if__invalid_range(void** state);
void test_algo_max_element_if__invalid_range2(void** state);
void test_algo_max_element_if__invalid_range3(void** state);
void test_algo_max_element_if__empty(void** state);
void test_algo_max_element_if__bfun_NULL_normal(void** state);
void test_algo_max_element_if__bfun_NULL_equal(void** state);
void test_algo_max_element_if__normal(void** state);
void test_algo_max_element_if__equal(void** state);
/*
 * test algo_min_element
 */
UT_CASE_DECLARATION(algo_min_element)
void test_algo_min_element__invalid_range(void** state);
void test_algo_min_element__invalid_range2(void** state);
void test_algo_min_element__invalid_range3(void** state);
void test_algo_min_element__empty(void** state);
void test_algo_min_element__normal(void** state);
void test_algo_min_element__equal(void** state);
/*
 * test algo_min_element_if
 */
UT_CASE_DECLARATION(algo_min_element_if)
void test_algo_min_element_if__invalid_range(void** state);
void test_algo_min_element_if__invalid_range2(void** state);
void test_algo_min_element_if__invalid_range3(void** state);
void test_algo_min_element_if__empty(void** state);
void test_algo_min_element_if__bfun_NULL_normal(void** state);
void test_algo_min_element_if__bfun_NULL_equal(void** state);
void test_algo_min_element_if__normal(void** state);
void test_algo_min_element_if__equal(void** state);
/*
 * test algo_lexicographical_compare
 */
UT_CASE_DECLARATION(algo_lexicographical_compare)
void test_algo_lexicographical_compare__invalid_first_range(void** state);
void test_algo_lexicographical_compare__invalid_second_range(void** state);
void test_algo_lexicographical_compare__not_same_type(void** state);
void test_algo_lexicographical_compare__first_empty(void** state);
void test_algo_lexicographical_compare__second_empty(void** state);
void test_algo_lexicographical_compare__all_empty(void** state);
void test_algo_lexicographical_compare__less(void** state);
void test_algo_lexicographical_compare__greater(void** state);
void test_algo_lexicographical_compare__equal(void** state);
/*
 * test algo_lexicographical_compare_if
 */
UT_CASE_DECLARATION(algo_lexicographical_compare_if)
void test_algo_lexicographical_compare_if__invalid_first_range(void** state);
void test_algo_lexicographical_compare_if__invalid_second_range(void** state);
void test_algo_lexicographical_compare_if__not_same_type(void** state);
void test_algo_lexicographical_compare_if__first_empty(void** state);
void test_algo_lexicographical_compare_if__second_empty(void** state);
void test_algo_lexicographical_compare_if__all_empty(void** state);
void test_algo_lexicographical_compare_if__bfun_NULL_less(void** state);
void test_algo_lexicographical_compare_if__bfun_NULL_greater(void** state);
void test_algo_lexicographical_compare_if__bfun_NULL_equal(void** state);
void test_algo_lexicographical_compare_if__less(void** state);
void test_algo_lexicographical_compare_if__greater(void** state);
void test_algo_lexicographical_compare_if__equal(void** state);
/*
 * test algo_lexicographical_compare_3way
 */
UT_CASE_DECLARATION(algo_lexicographical_compare_3way)
void test_algo_lexicographical_compare_3way__invalid_first_range(void** state);
void test_algo_lexicographical_compare_3way__invalid_second_range(void** state);
void test_algo_lexicographical_compare_3way__not_same_type(void** state);
void test_algo_lexicographical_compare_3way__first_empty(void** state);
void test_algo_lexicographical_compare_3way__second_empty(void** state);
void test_algo_lexicographical_compare_3way__all_empty(void** state);
void test_algo_lexicographical_compare_3way__less(void** state);
void test_algo_lexicographical_compare_3way__greater(void** state);
void test_algo_lexicographical_compare_3way__equal(void** state);
/*
 * test algo_lexicographical_compare_3way_if
 */
UT_CASE_DECLARATION(algo_lexicographical_compare_3way_if)
void test_algo_lexicographical_compare_3way_if__invalid_first_range(void** state);
void test_algo_lexicographical_compare_3way_if__invalid_second_range(void** state);
void test_algo_lexicographical_compare_3way_if__not_same_type(void** state);
void test_algo_lexicographical_compare_3way_if__first_empty(void** state);
void test_algo_lexicographical_compare_3way_if__second_empty(void** state);
void test_algo_lexicographical_compare_3way_if__all_empty(void** state);
void test_algo_lexicographical_compare_3way_if__bfun_NULL_less(void** state);
void test_algo_lexicographical_compare_3way_if__bfun_NULL_greater(void** state);
void test_algo_lexicographical_compare_3way_if__bfun_NULL_equal(void** state);
void test_algo_lexicographical_compare_3way_if__less(void** state);
void test_algo_lexicographical_compare_3way_if__greater(void** state);
void test_algo_lexicographical_compare_3way_if__equal(void** state);
/*
 * test algo_next_permutation
 */
UT_CASE_DECLARATION(algo_next_permutation)
void test_algo_next_permutation__invalid_range(void** state);
void test_algo_next_permutation__invalid_range2(void** state);
void test_algo_next_permutation__invalid_range3(void** state);
void test_algo_next_permutation__empty(void** state);
void test_algo_next_permutation__equal(void** state);
void test_algo_next_permutation__first(void** state);
void test_algo_next_permutation__middle(void** state);
void test_algo_next_permutation__last(void** state);
/*
 * test algo_next_permutation_if
 */
UT_CASE_DECLARATION(algo_next_permutation_if)
void test_algo_next_permutation_if__invalid_range(void** state);
void test_algo_next_permutation_if__invalid_range2(void** state);
void test_algo_next_permutation_if__invalid_range3(void** state);
void test_algo_next_permutation_if__empty(void** state);
void test_algo_next_permutation_if__equal(void** state);
void test_algo_next_permutation_if__bfun_NULL_first(void** state);
void test_algo_next_permutation_if__bfun_NULL_middle(void** state);
void test_algo_next_permutation_if__bfun_NULL_last(void** state);
void test_algo_next_permutation_if__first(void** state);
void test_algo_next_permutation_if__middle(void** state);
void test_algo_next_permutation_if__last(void** state);
/*
 * test algo_prev_permutation
 */
UT_CASE_DECLARATION(algo_prev_permutation)
void test_algo_prev_permutation__invalid_range(void** state);
void test_algo_prev_permutation__invalid_range2(void** state);
void test_algo_prev_permutation__invalid_range3(void** state);
void test_algo_prev_permutation__empty(void** state);
void test_algo_prev_permutation__equal(void** state);
void test_algo_prev_permutation__first(void** state);
void test_algo_prev_permutation__middle(void** state);
void test_algo_prev_permutation__last(void** state);
/*
 * test algo_prev_permutation_if
 */
UT_CASE_DECLARATION(algo_prev_permutation_if)
void test_algo_prev_permutation_if__invalid_range(void** state);
void test_algo_prev_permutation_if__invalid_range2(void** state);
void test_algo_prev_permutation_if__invalid_range3(void** state);
void test_algo_prev_permutation_if__empty(void** state);
void test_algo_prev_permutation_if__equal(void** state);
void test_algo_prev_permutation_if__bfun_NULL_first(void** state);
void test_algo_prev_permutation_if__bfun_NULL_middle(void** state);
void test_algo_prev_permutation_if__bfun_NULL_last(void** state);
void test_algo_prev_permutation_if__first(void** state);
void test_algo_prev_permutation_if__middle(void** state);
void test_algo_prev_permutation_if__last(void** state);

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
    UT_CASE(test_algo_stable_sort_if__more_than_threshold),\
    UT_CASE_BEGIN(algo_nth_element, test_algo_nth_element__invalid_first_range),\
    UT_CASE(test_algo_nth_element__invalid_second_range),\
    UT_CASE(test_algo_nth_element__invalid_range),\
    UT_CASE(test_algo_nth_element__empty),\
    UT_CASE(test_algo_nth_element__three),\
    UT_CASE(test_algo_nth_element__first_element),\
    UT_CASE(test_algo_nth_element__last_element),\
    UT_CASE(test_algo_nth_element__normal),\
    UT_CASE(test_algo_nth_element__last),\
    UT_CASE_BEGIN(algo_nth_element_if, test_algo_nth_element_if__invalid_first_range),\
    UT_CASE(test_algo_nth_element_if__invalid_second_range),\
    UT_CASE(test_algo_nth_element_if__invalid_range),\
    UT_CASE(test_algo_nth_element_if__empty),\
    UT_CASE(test_algo_nth_element_if__three),\
    UT_CASE(test_algo_nth_element_if__first_element),\
    UT_CASE(test_algo_nth_element_if__last_element),\
    UT_CASE(test_algo_nth_element_if__normal),\
    UT_CASE(test_algo_nth_element_if__last),\
    UT_CASE(test_algo_nth_element_if__bfun_NULL_first_element),\
    UT_CASE(test_algo_nth_element_if__bfun_NULL_last_element),\
    UT_CASE(test_algo_nth_element_if__bfun_NULL_normal),\
    UT_CASE(test_algo_nth_element_if__bfun_NULL_last),\
    UT_CASE(test_algo_nth_element_if__last),\
    UT_CASE_BEGIN(algo_includes, test_algo_includes__invalid_first_range),\
    UT_CASE(test_algo_includes__invalid_second_range),\
    UT_CASE(test_algo_includes__not_same_type),\
    UT_CASE(test_algo_includes__first_empty),\
    UT_CASE(test_algo_includes__second_empty),\
    UT_CASE(test_algo_includes__all_empty),\
    UT_CASE(test_algo_includes__true),\
    UT_CASE(test_algo_includes__false),\
    UT_CASE_BEGIN(algo_includes_if, test_algo_includes_if__invalid_first_range),\
    UT_CASE(test_algo_includes_if__invalid_second_range),\
    UT_CASE(test_algo_includes_if__not_same_type),\
    UT_CASE(test_algo_includes_if__first_empty),\
    UT_CASE(test_algo_includes_if__second_empty),\
    UT_CASE(test_algo_includes_if__all_empty),\
    UT_CASE(test_algo_includes_if__bfun_NULL_true),\
    UT_CASE(test_algo_includes_if__bfun_NULL_false),\
    UT_CASE(test_algo_includes_if__true),\
    UT_CASE(test_algo_includes_if__false),\
    UT_CASE_BEGIN(algo_set_union, test_algo_set_union__invalid_first_range),\
    UT_CASE(test_algo_set_union__invalid_second_range),\
    UT_CASE(test_algo_set_union__invalid_third_range),\
    UT_CASE(test_algo_set_union__first_not_same_type),\
    UT_CASE(test_algo_set_union__second_not_same_type),\
    UT_CASE(test_algo_set_union__third_not_same_type),\
    UT_CASE(test_algo_set_union__first_empty),\
    UT_CASE(test_algo_set_union__second_empty),\
    UT_CASE(test_algo_set_union__all_empty),\
    UT_CASE(test_algo_set_union__first_lead_second),\
    UT_CASE(test_algo_set_union__first_overlap_second),\
    UT_CASE(test_algo_set_union__second_overlap_first),\
    UT_CASE(test_algo_set_union__second_lead_first),\
    UT_CASE_BEGIN(algo_set_union_if, test_algo_set_union_if__invalid_first_range),\
    UT_CASE(test_algo_set_union_if__invalid_second_range),\
    UT_CASE(test_algo_set_union_if__invalid_third_range),\
    UT_CASE(test_algo_set_union_if__first_not_same_type),\
    UT_CASE(test_algo_set_union_if__second_not_same_type),\
    UT_CASE(test_algo_set_union_if__third_not_same_type),\
    UT_CASE(test_algo_set_union_if__bfun_NULL_first_lead_second),\
    UT_CASE(test_algo_set_union_if__bfun_NULL_first_overlap_second),\
    UT_CASE(test_algo_set_union_if__bfun_NULL_second_overlap_first),\
    UT_CASE(test_algo_set_union_if__bfun_NULL_second_lead_first),\
    UT_CASE(test_algo_set_union_if__first_lead_second),\
    UT_CASE(test_algo_set_union_if__first_overlap_second),\
    UT_CASE(test_algo_set_union_if__second_overlap_first),\
    UT_CASE(test_algo_set_union_if__second_lead_first),\
    UT_CASE_BEGIN(algo_set_intersection, test_algo_set_intersection__invalid_first_range),\
    UT_CASE(test_algo_set_intersection__invalid_second_range),\
    UT_CASE(test_algo_set_intersection__invalid_third_range),\
    UT_CASE(test_algo_set_intersection__first_not_same_type),\
    UT_CASE(test_algo_set_intersection__second_not_same_type),\
    UT_CASE(test_algo_set_intersection__third_not_same_type),\
    UT_CASE(test_algo_set_intersection__result_empty),\
    UT_CASE(test_algo_set_intersection__result_not_empty),\
    UT_CASE_BEGIN(algo_set_intersection_if, test_algo_set_intersection_if__invalid_first_range),\
    UT_CASE(test_algo_set_intersection_if__invalid_second_range),\
    UT_CASE(test_algo_set_intersection_if__invalid_third_range),\
    UT_CASE(test_algo_set_intersection_if__first_not_same_type),\
    UT_CASE(test_algo_set_intersection_if__second_not_same_type),\
    UT_CASE(test_algo_set_intersection_if__third_not_same_type),\
    UT_CASE(test_algo_set_intersection_if__bfun_NULL_result_empty),\
    UT_CASE(test_algo_set_intersection_if__bfun_NULL_result_not_empty),\
    UT_CASE(test_algo_set_intersection_if__result_empty),\
    UT_CASE(test_algo_set_intersection_if__result_not_empty),\
    UT_CASE_BEGIN(algo_set_difference, test_algo_set_difference__invalid_first_range),\
    UT_CASE(test_algo_set_difference__invalid_second_range),\
    UT_CASE(test_algo_set_difference__invalid_third_range),\
    UT_CASE(test_algo_set_difference__first_not_same_type),\
    UT_CASE(test_algo_set_difference__second_not_same_type),\
    UT_CASE(test_algo_set_difference__third_not_same_type),\
    UT_CASE(test_algo_set_difference__result_difference),\
    UT_CASE(test_algo_set_difference__result_not_difference),\
    UT_CASE_BEGIN(algo_set_difference_if, test_algo_set_difference_if__invalid_first_range),\
    UT_CASE(test_algo_set_difference_if__invalid_second_range),\
    UT_CASE(test_algo_set_difference_if__invalid_third_range),\
    UT_CASE(test_algo_set_difference_if__first_not_same_type),\
    UT_CASE(test_algo_set_difference_if__second_not_same_type),\
    UT_CASE(test_algo_set_difference_if__third_not_same_type),\
    UT_CASE(test_algo_set_difference_if__bfun_NULL_result_difference),\
    UT_CASE(test_algo_set_difference_if__bfun_NULL_result_not_difference),\
    UT_CASE(test_algo_set_difference_if__result_difference),\
    UT_CASE(test_algo_set_difference_if__result_not_difference),\
    UT_CASE_BEGIN(algo_set_symmetric_difference, test_algo_set_symmetric_difference__invalid_first_range),\
    UT_CASE(test_algo_set_symmetric_difference__invalid_second_range),\
    UT_CASE(test_algo_set_symmetric_difference__invalid_third_range),\
    UT_CASE(test_algo_set_symmetric_difference__first_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference__second_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference__third_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference__result_difference),\
    UT_CASE(test_algo_set_symmetric_difference__result_not_difference),\
    UT_CASE_BEGIN(algo_set_symmetric_difference_if, test_algo_set_symmetric_difference_if__invalid_first_range),\
    UT_CASE(test_algo_set_symmetric_difference_if__invalid_second_range),\
    UT_CASE(test_algo_set_symmetric_difference_if__invalid_third_range),\
    UT_CASE(test_algo_set_symmetric_difference_if__first_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference_if__second_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference_if__third_not_same_type),\
    UT_CASE(test_algo_set_symmetric_difference_if__bfun_NULL_result_difference),\
    UT_CASE(test_algo_set_symmetric_difference_if__bfun_NULL_result_not_difference),\
    UT_CASE(test_algo_set_symmetric_difference_if__result_difference),\
    UT_CASE(test_algo_set_symmetric_difference_if__result_not_difference),\
    UT_CASE_BEGIN(algo_max, test_algo_max__not_same_type),\
    UT_CASE(test_algo_max__first_max),\
    UT_CASE(test_algo_max__second_max),\
    UT_CASE(test_algo_max__equal),\
    UT_CASE_BEGIN(algo_max_if, test_algo_max_if__not_same_type),\
    UT_CASE(test_algo_max_if__equal),\
    UT_CASE(test_algo_max_if__bfun_NULL_first_max),\
    UT_CASE(test_algo_max_if__bfun_NULL_second_max),\
    UT_CASE(test_algo_max_if__first_max),\
    UT_CASE(test_algo_max_if__second_max),\
    UT_CASE_BEGIN(algo_min, test_algo_min__not_same_type),\
    UT_CASE(test_algo_min__first_min),\
    UT_CASE(test_algo_min__second_min),\
    UT_CASE(test_algo_min__equal),\
    UT_CASE_BEGIN(algo_min_if, test_algo_min_if__not_same_type),\
    UT_CASE(test_algo_min_if__equal),\
    UT_CASE(test_algo_min_if__bfun_NULL_first_min),\
    UT_CASE(test_algo_min_if__bfun_NULL_second_min),\
    UT_CASE(test_algo_min_if__first_min),\
    UT_CASE(test_algo_min_if__second_min),\
    UT_CASE_BEGIN(algo_max_element, test_algo_max_element__invalid_range),\
    UT_CASE(test_algo_max_element__invalid_range2),\
    UT_CASE(test_algo_max_element__invalid_range3),\
    UT_CASE(test_algo_max_element__empty),\
    UT_CASE(test_algo_max_element__normal),\
    UT_CASE(test_algo_max_element__equal),\
    UT_CASE_BEGIN(algo_max_element_if, test_algo_max_element_if__invalid_range),\
    UT_CASE(test_algo_max_element_if__invalid_range2),\
    UT_CASE(test_algo_max_element_if__invalid_range3),\
    UT_CASE(test_algo_max_element_if__empty),\
    UT_CASE(test_algo_max_element_if__bfun_NULL_normal),\
    UT_CASE(test_algo_max_element_if__bfun_NULL_equal),\
    UT_CASE(test_algo_max_element_if__normal),\
    UT_CASE(test_algo_max_element_if__equal),\
    UT_CASE_BEGIN(algo_min_element, test_algo_min_element__invalid_range),\
    UT_CASE(test_algo_min_element__invalid_range2),\
    UT_CASE(test_algo_min_element__invalid_range3),\
    UT_CASE(test_algo_min_element__empty),\
    UT_CASE(test_algo_min_element__normal),\
    UT_CASE(test_algo_min_element__equal),\
    UT_CASE_BEGIN(algo_min_element_if, test_algo_min_element_if__invalid_range),\
    UT_CASE(test_algo_min_element_if__invalid_range2),\
    UT_CASE(test_algo_min_element_if__invalid_range3),\
    UT_CASE(test_algo_min_element_if__empty),\
    UT_CASE(test_algo_min_element_if__bfun_NULL_normal),\
    UT_CASE(test_algo_min_element_if__bfun_NULL_equal),\
    UT_CASE(test_algo_min_element_if__normal),\
    UT_CASE(test_algo_min_element_if__equal),\
    UT_CASE_BEGIN(algo_lexicographical_compare, test_algo_lexicographical_compare__invalid_first_range),\
    UT_CASE(test_algo_lexicographical_compare__invalid_second_range),\
    UT_CASE(test_algo_lexicographical_compare__not_same_type),\
    UT_CASE(test_algo_lexicographical_compare__first_empty),\
    UT_CASE(test_algo_lexicographical_compare__second_empty),\
    UT_CASE(test_algo_lexicographical_compare__all_empty),\
    UT_CASE(test_algo_lexicographical_compare__less),\
    UT_CASE(test_algo_lexicographical_compare__greater),\
    UT_CASE(test_algo_lexicographical_compare__equal),\
    UT_CASE_BEGIN(algo_lexicographical_compare_if, test_algo_lexicographical_compare_if__invalid_first_range),\
    UT_CASE(test_algo_lexicographical_compare_if__invalid_second_range),\
    UT_CASE(test_algo_lexicographical_compare_if__not_same_type),\
    UT_CASE(test_algo_lexicographical_compare_if__first_empty),\
    UT_CASE(test_algo_lexicographical_compare_if__second_empty),\
    UT_CASE(test_algo_lexicographical_compare_if__all_empty),\
    UT_CASE(test_algo_lexicographical_compare_if__bfun_NULL_less),\
    UT_CASE(test_algo_lexicographical_compare_if__bfun_NULL_greater),\
    UT_CASE(test_algo_lexicographical_compare_if__bfun_NULL_equal),\
    UT_CASE(test_algo_lexicographical_compare_if__less),\
    UT_CASE(test_algo_lexicographical_compare_if__greater),\
    UT_CASE(test_algo_lexicographical_compare_if__equal),\
    UT_CASE_BEGIN(algo_lexicographical_compare_3way, test_algo_lexicographical_compare_3way__invalid_first_range),\
    UT_CASE(test_algo_lexicographical_compare_3way__invalid_second_range),\
    UT_CASE(test_algo_lexicographical_compare_3way__not_same_type),\
    UT_CASE(test_algo_lexicographical_compare_3way__first_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way__second_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way__all_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way__less),\
    UT_CASE(test_algo_lexicographical_compare_3way__greater),\
    UT_CASE(test_algo_lexicographical_compare_3way__equal),\
    UT_CASE_BEGIN(algo_lexicographical_compare_3way_if, test_algo_lexicographical_compare_3way_if__invalid_first_range),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__invalid_second_range),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__not_same_type),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__first_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__second_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__all_empty),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__bfun_NULL_less),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__bfun_NULL_greater),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__bfun_NULL_equal),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__less),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__greater),\
    UT_CASE(test_algo_lexicographical_compare_3way_if__equal),\
    UT_CASE_BEGIN(algo_next_permutation, test_algo_next_permutation__invalid_range),\
    UT_CASE(test_algo_next_permutation__invalid_range2),\
    UT_CASE(test_algo_next_permutation__invalid_range3),\
    UT_CASE(test_algo_next_permutation__empty),\
    UT_CASE(test_algo_next_permutation__equal),\
    UT_CASE(test_algo_next_permutation__first),\
    UT_CASE(test_algo_next_permutation__middle),\
    UT_CASE(test_algo_next_permutation__last),\
    UT_CASE_BEGIN(algo_next_permutation_if, test_algo_next_permutation_if__invalid_range),\
    UT_CASE(test_algo_next_permutation_if__invalid_range2),\
    UT_CASE(test_algo_next_permutation_if__invalid_range3),\
    UT_CASE(test_algo_next_permutation_if__empty),\
    UT_CASE(test_algo_next_permutation_if__equal),\
    UT_CASE(test_algo_next_permutation_if__bfun_NULL_first),\
    UT_CASE(test_algo_next_permutation_if__bfun_NULL_middle),\
    UT_CASE(test_algo_next_permutation_if__bfun_NULL_last),\
    UT_CASE(test_algo_next_permutation_if__first),\
    UT_CASE(test_algo_next_permutation_if__middle),\
    UT_CASE(test_algo_next_permutation_if__last),\
    UT_CASE_BEGIN(algo_prev_permutation, test_algo_prev_permutation__invalid_range),\
    UT_CASE(test_algo_prev_permutation__invalid_range2),\
    UT_CASE(test_algo_prev_permutation__invalid_range3),\
    UT_CASE(test_algo_prev_permutation__empty),\
    UT_CASE(test_algo_prev_permutation__equal),\
    UT_CASE(test_algo_prev_permutation__first),\
    UT_CASE(test_algo_prev_permutation__middle),\
    UT_CASE(test_algo_prev_permutation__last),\
    UT_CASE_BEGIN(algo_prev_permutation_if, test_algo_prev_permutation_if__invalid_range),\
    UT_CASE(test_algo_prev_permutation_if__invalid_range2),\
    UT_CASE(test_algo_prev_permutation_if__invalid_range3),\
    UT_CASE(test_algo_prev_permutation_if__empty),\
    UT_CASE(test_algo_prev_permutation_if__equal),\
    UT_CASE(test_algo_prev_permutation_if__bfun_NULL_first),\
    UT_CASE(test_algo_prev_permutation_if__bfun_NULL_middle),\
    UT_CASE(test_algo_prev_permutation_if__bfun_NULL_last),\
    UT_CASE(test_algo_prev_permutation_if__first),\
    UT_CASE(test_algo_prev_permutation_if__middle),\
    UT_CASE(test_algo_prev_permutation_if__last)

#endif /* _UT_CSTL_ALGO_SORTING_H_ */

