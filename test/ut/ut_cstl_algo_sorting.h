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
    UT_CASE(test_algo_partial_sort_copy_if__first_greater_second)

#endif /* _UT_CSTL_ALGO_SORTING_H_ */

