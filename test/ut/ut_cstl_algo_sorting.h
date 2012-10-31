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
    UT_CASE(test_algo_partial_sort__invalid_range3)

#endif /* _UT_CSTL_ALGO_SORTING_H_ */

