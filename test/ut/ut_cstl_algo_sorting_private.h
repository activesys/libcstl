#ifndef _UT_CSTL_ALGO_SORTING_PRIVATE_H_
#define _UT_CSTL_ALGO_SORTING_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_algo_sorting_private)

/*
 * test _algo_lower_bound
 */
UT_CASE_DECLARATION(_algo_lower_bound)
void test__algo_lower_bound__invalid_range(void** state);
void test__algo_lower_bound__invalid_range2(void** state);
void test__algo_lower_bound__invalid_range3(void** state);
void test__algo_lower_bound__empty(void** state);
void test__algo_lower_bound__all_greater(void** state);
void test__algo_lower_bound__all_greater_equal(void** state);
void test__algo_lower_bound__greater(void** state);
void test__algo_lower_bound__greater_equal(void** state);
void test__algo_lower_bound__all_less_equal(void** state);
void test__algo_lower_bound__all_less(void** state);
void test__algo_lower_bound__cstr_all_greater(void** state);
void test__algo_lower_bound__cstr_all_greater_equal(void** state);
void test__algo_lower_bound__cstr_greater(void** state);
void test__algo_lower_bound__cstr_greater_equal(void** state);
void test__algo_lower_bound__cstr_all_less_equal(void** state);
void test__algo_lower_bound__cstr_all_less(void** state);
/*
 * test _algo_lower_bound_if
 */
UT_CASE_DECLARATION(_algo_lower_bound_if)
void test__algo_lower_bound_if__invalid_range(void** state);
void test__algo_lower_bound_if__invalid_range2(void** state);
void test__algo_lower_bound_if__invalid_range3(void** state);
void test__algo_lower_bound_if__empty(void** state);
void test__algo_lower_bound_if__bfun_NULL_all_greater(void** state);
void test__algo_lower_bound_if__bfun_NULL_all_greater_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_greater(void** state);
void test__algo_lower_bound_if__bfun_NULL_greater_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_all_less_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_all_less(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_all_greater(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_all_greater_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_greater(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_greater_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_all_less_equal(void** state);
void test__algo_lower_bound_if__bfun_NULL_cstr_all_less(void** state);
void test__algo_lower_bound_if___all_greater(void** state);
void test__algo_lower_bound_if___all_greater_equal(void** state);
void test__algo_lower_bound_if___greater(void** state);
void test__algo_lower_bound_if___greater_equal(void** state);
void test__algo_lower_bound_if___all_less_equal(void** state);
void test__algo_lower_bound_if___all_less(void** state);
void test__algo_lower_bound_if___cstr_all_greater(void** state);
void test__algo_lower_bound_if___cstr_all_greater_equal(void** state);
void test__algo_lower_bound_if___cstr_greater(void** state);
void test__algo_lower_bound_if___cstr_greater_equal(void** state);
void test__algo_lower_bound_if___cstr_all_less_equal(void** state);
void test__algo_lower_bound_if___cstr_all_less(void** state);
/*
 * test _algo_upper_bound
 */
UT_CASE_DECLARATION(_algo_upper_bound)
void test__algo_upper_bound__invalid_range(void** state);
void test__algo_upper_bound__invalid_range2(void** state);
void test__algo_upper_bound__invalid_range3(void** state);
void test__algo_upper_bound__empty(void** state);
void test__algo_upper_bound__all_greater(void** state);
void test__algo_upper_bound__all_greater_equal(void** state);
void test__algo_upper_bound__greater(void** state);
void test__algo_upper_bound__greater_equal(void** state);
void test__algo_upper_bound__all_less_equal(void** state);
void test__algo_upper_bound__all_less(void** state);
void test__algo_upper_bound__cstr_all_greater(void** state);
void test__algo_upper_bound__cstr_all_greater_equal(void** state);
void test__algo_upper_bound__cstr_greater(void** state);
void test__algo_upper_bound__cstr_greater_equal(void** state);
void test__algo_upper_bound__cstr_all_less_equal(void** state);
void test__algo_upper_bound__cstr_all_less(void** state);
/*
 * test _algo_upper_bound_if
 */
UT_CASE_DECLARATION(_algo_upper_bound_if)
void test__algo_upper_bound_if__invalid_range(void** state);
void test__algo_upper_bound_if__invalid_range2(void** state);
void test__algo_upper_bound_if__invalid_range3(void** state);
void test__algo_upper_bound_if__empty(void** state);
void test__algo_upper_bound_if__bfun_NULL_all_greater(void** state);
void test__algo_upper_bound_if__bfun_NULL_all_greater_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_greater(void** state);
void test__algo_upper_bound_if__bfun_NULL_greater_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_all_less_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_all_less(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_all_greater(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_all_greater_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_greater(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_greater_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_all_less_equal(void** state);
void test__algo_upper_bound_if__bfun_NULL_cstr_all_less(void** state);
void test__algo_upper_bound_if___all_greater(void** state);
void test__algo_upper_bound_if___all_greater_equal(void** state);
void test__algo_upper_bound_if___greater(void** state);
void test__algo_upper_bound_if___greater_equal(void** state);
void test__algo_upper_bound_if___all_less_equal(void** state);
void test__algo_upper_bound_if___all_less(void** state);
void test__algo_upper_bound_if___cstr_all_greater(void** state);
void test__algo_upper_bound_if___cstr_all_greater_equal(void** state);
void test__algo_upper_bound_if___cstr_greater(void** state);
void test__algo_upper_bound_if___cstr_greater_equal(void** state);
void test__algo_upper_bound_if___cstr_all_less_equal(void** state);
void test__algo_upper_bound_if___cstr_all_less(void** state);
/*
 * test _algo_equal_range
 */
UT_CASE_DECLARATION(_algo_equal_range)
void test__algo_equal_range__invalid_range(void** state);
void test__algo_equal_range__invalid_range2(void** state);
void test__algo_equal_range__invalid_range3(void** state);
void test__algo_equal_range__empty(void** state);
void test__algo_equal_range__all_greater(void** state);
void test__algo_equal_range__all_greater_equal(void** state);
void test__algo_equal_range__greater(void** state);
void test__algo_equal_range__greater_equal(void** state);
void test__algo_equal_range__all_less_equal(void** state);
void test__algo_equal_range__all_less(void** state);
void test__algo_equal_range__cstr_all_greater(void** state);
void test__algo_equal_range__cstr_all_greater_equal(void** state);
void test__algo_equal_range__cstr_greater(void** state);
void test__algo_equal_range__cstr_greater_equal(void** state);
void test__algo_equal_range__cstr_all_less_equal(void** state);
void test__algo_equal_range__cstr_all_less(void** state);
/*
 * test _algo_equal_range_if
 */
UT_CASE_DECLARATION(_algo_equal_range_if)
void test__algo_equal_range_if__invalid_range(void** state);
void test__algo_equal_range_if__invalid_range2(void** state);
void test__algo_equal_range_if__invalid_range3(void** state);
void test__algo_equal_range_if__empty(void** state);
void test__algo_equal_range_if__bfun_NULL_all_greater(void** state);
void test__algo_equal_range_if__bfun_NULL_all_greater_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_greater(void** state);
void test__algo_equal_range_if__bfun_NULL_greater_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_all_less_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_all_less(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_all_greater(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_all_greater_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_greater(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_greater_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_all_less_equal(void** state);
void test__algo_equal_range_if__bfun_NULL_cstr_all_less(void** state);
void test__algo_equal_range_if___all_greater(void** state);
void test__algo_equal_range_if___all_greater_equal(void** state);
void test__algo_equal_range_if___greater(void** state);
void test__algo_equal_range_if___greater_equal(void** state);
void test__algo_equal_range_if___all_less_equal(void** state);
void test__algo_equal_range_if___all_less(void** state);
void test__algo_equal_range_if___cstr_all_greater(void** state);
void test__algo_equal_range_if___cstr_all_greater_equal(void** state);
void test__algo_equal_range_if___cstr_greater(void** state);
void test__algo_equal_range_if___cstr_greater_equal(void** state);
void test__algo_equal_range_if___cstr_all_less_equal(void** state);
void test__algo_equal_range_if___cstr_all_less(void** state);
/*
 * test _algo_binary_search
 */
UT_CASE_DECLARATION(_algo_binary_search)
void test__algo_binary_search__invalid_range(void** state);
void test__algo_binary_search__invalid_range2(void** state);
void test__algo_binary_search__invalid_range3(void** state);
void test__algo_binary_search__empty(void** state);
void test__algo_binary_search__true(void** state);
void test__algo_binary_search__false(void** state);
void test__algo_binary_search__cstr_true(void** state);
void test__algo_binary_search__cstr_false(void** state);
/*
 * test _algo_binary_search_if
 */
UT_CASE_DECLARATION(_algo_binary_search_if)
void test__algo_binary_search_if__invalid_range(void** state);
void test__algo_binary_search_if__invalid_range2(void** state);
void test__algo_binary_search_if__invalid_range3(void** state);
void test__algo_binary_search_if__empty(void** state);
void test__algo_binary_search_if__bfun_NULL_true(void** state);
void test__algo_binary_search_if__bfun_NULL_false(void** state);
void test__algo_binary_search_if__bfun_NULL_cstr_true(void** state);
void test__algo_binary_search_if__bfun_NULL_cstr_false(void** state);
void test__algo_binary_search_if__true(void** state);
void test__algo_binary_search_if__false(void** state);
void test__algo_binary_search_if__cstr_true(void** state);
void test__algo_binary_search_if__cstr_false(void** state);

#define UT_CSTL_ALGO_SORTING_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_algo_sorting_private, test__algo_lower_bound__invalid_range),\
    UT_CASE(test__algo_lower_bound__invalid_range2),\
    UT_CASE(test__algo_lower_bound__invalid_range3),\
    UT_CASE(test__algo_lower_bound__empty),\
    UT_CASE(test__algo_lower_bound__all_greater),\
    UT_CASE(test__algo_lower_bound__all_greater_equal),\
    UT_CASE(test__algo_lower_bound__greater),\
    UT_CASE(test__algo_lower_bound__greater_equal),\
    UT_CASE(test__algo_lower_bound__all_less_equal),\
    UT_CASE(test__algo_lower_bound__all_less),\
    UT_CASE(test__algo_lower_bound__cstr_all_greater),\
    UT_CASE(test__algo_lower_bound__cstr_all_greater_equal),\
    UT_CASE(test__algo_lower_bound__cstr_greater),\
    UT_CASE(test__algo_lower_bound__cstr_greater_equal),\
    UT_CASE(test__algo_lower_bound__cstr_all_less_equal),\
    UT_CASE(test__algo_lower_bound__cstr_all_less),\
    UT_CASE_BEGIN(_algo_lower_bound_if, test__algo_lower_bound_if__invalid_range),\
    UT_CASE(test__algo_lower_bound_if__invalid_range2),\
    UT_CASE(test__algo_lower_bound_if__invalid_range3),\
    UT_CASE(test__algo_lower_bound_if__empty),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_all_greater),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_all_greater_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_greater),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_greater_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_all_less_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_all_less),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_all_greater),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_all_greater_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_greater),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_greater_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_all_less_equal),\
    UT_CASE(test__algo_lower_bound_if__bfun_NULL_cstr_all_less),\
    UT_CASE(test__algo_lower_bound_if___all_greater),\
    UT_CASE(test__algo_lower_bound_if___all_greater_equal),\
    UT_CASE(test__algo_lower_bound_if___greater),\
    UT_CASE(test__algo_lower_bound_if___greater_equal),\
    UT_CASE(test__algo_lower_bound_if___all_less_equal),\
    UT_CASE(test__algo_lower_bound_if___all_less),\
    UT_CASE(test__algo_lower_bound_if___cstr_all_greater),\
    UT_CASE(test__algo_lower_bound_if___cstr_all_greater_equal),\
    UT_CASE(test__algo_lower_bound_if___cstr_greater),\
    UT_CASE(test__algo_lower_bound_if___cstr_greater_equal),\
    UT_CASE(test__algo_lower_bound_if___cstr_all_less_equal),\
    UT_CASE(test__algo_lower_bound_if___cstr_all_less),\
    UT_CASE_BEGIN(_algo_upper_bound, test__algo_upper_bound__invalid_range),\
    UT_CASE(test__algo_upper_bound__invalid_range2),\
    UT_CASE(test__algo_upper_bound__invalid_range3),\
    UT_CASE(test__algo_upper_bound__empty),\
    UT_CASE(test__algo_upper_bound__all_greater),\
    UT_CASE(test__algo_upper_bound__all_greater_equal),\
    UT_CASE(test__algo_upper_bound__greater),\
    UT_CASE(test__algo_upper_bound__greater_equal),\
    UT_CASE(test__algo_upper_bound__all_less_equal),\
    UT_CASE(test__algo_upper_bound__all_less),\
    UT_CASE(test__algo_upper_bound__cstr_all_greater),\
    UT_CASE(test__algo_upper_bound__cstr_all_greater_equal),\
    UT_CASE(test__algo_upper_bound__cstr_greater),\
    UT_CASE(test__algo_upper_bound__cstr_greater_equal),\
    UT_CASE(test__algo_upper_bound__cstr_all_less_equal),\
    UT_CASE(test__algo_upper_bound__cstr_all_less),\
    UT_CASE_BEGIN(_algo_upper_bound_if, test__algo_upper_bound_if__invalid_range),\
    UT_CASE(test__algo_upper_bound_if__invalid_range2),\
    UT_CASE(test__algo_upper_bound_if__invalid_range3),\
    UT_CASE(test__algo_upper_bound_if__empty),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_all_greater),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_all_greater_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_greater),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_greater_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_all_less_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_all_less),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_all_greater),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_all_greater_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_greater),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_greater_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_all_less_equal),\
    UT_CASE(test__algo_upper_bound_if__bfun_NULL_cstr_all_less),\
    UT_CASE(test__algo_upper_bound_if___all_greater),\
    UT_CASE(test__algo_upper_bound_if___all_greater_equal),\
    UT_CASE(test__algo_upper_bound_if___greater),\
    UT_CASE(test__algo_upper_bound_if___greater_equal),\
    UT_CASE(test__algo_upper_bound_if___all_less_equal),\
    UT_CASE(test__algo_upper_bound_if___all_less),\
    UT_CASE(test__algo_upper_bound_if___cstr_all_greater),\
    UT_CASE(test__algo_upper_bound_if___cstr_all_greater_equal),\
    UT_CASE(test__algo_upper_bound_if___cstr_greater),\
    UT_CASE(test__algo_upper_bound_if___cstr_greater_equal),\
    UT_CASE(test__algo_upper_bound_if___cstr_all_less_equal),\
    UT_CASE(test__algo_upper_bound_if___cstr_all_less),\
    UT_CASE_BEGIN(_algo_equal_range, test__algo_equal_range__invalid_range),\
    UT_CASE(test__algo_equal_range__invalid_range2),\
    UT_CASE(test__algo_equal_range__invalid_range3),\
    UT_CASE(test__algo_equal_range__empty),\
    UT_CASE(test__algo_equal_range__all_greater),\
    UT_CASE(test__algo_equal_range__all_greater_equal),\
    UT_CASE(test__algo_equal_range__greater),\
    UT_CASE(test__algo_equal_range__greater_equal),\
    UT_CASE(test__algo_equal_range__all_less_equal),\
    UT_CASE(test__algo_equal_range__all_less),\
    UT_CASE(test__algo_equal_range__cstr_all_greater),\
    UT_CASE(test__algo_equal_range__cstr_all_greater_equal),\
    UT_CASE(test__algo_equal_range__cstr_greater),\
    UT_CASE(test__algo_equal_range__cstr_greater_equal),\
    UT_CASE(test__algo_equal_range__cstr_all_less_equal),\
    UT_CASE(test__algo_equal_range__cstr_all_less),\
    UT_CASE_BEGIN(_algo_equal_range_if, test__algo_equal_range_if__invalid_range),\
    UT_CASE(test__algo_equal_range_if__invalid_range2),\
    UT_CASE(test__algo_equal_range_if__invalid_range3),\
    UT_CASE(test__algo_equal_range_if__empty),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_all_greater),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_all_greater_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_greater),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_greater_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_all_less_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_all_less),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_all_greater),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_all_greater_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_greater),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_greater_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_all_less_equal),\
    UT_CASE(test__algo_equal_range_if__bfun_NULL_cstr_all_less),\
    UT_CASE(test__algo_equal_range_if___all_greater),\
    UT_CASE(test__algo_equal_range_if___all_greater_equal),\
    UT_CASE(test__algo_equal_range_if___greater),\
    UT_CASE(test__algo_equal_range_if___greater_equal),\
    UT_CASE(test__algo_equal_range_if___all_less_equal),\
    UT_CASE(test__algo_equal_range_if___all_less),\
    UT_CASE(test__algo_equal_range_if___cstr_all_greater),\
    UT_CASE(test__algo_equal_range_if___cstr_all_greater_equal),\
    UT_CASE(test__algo_equal_range_if___cstr_greater),\
    UT_CASE(test__algo_equal_range_if___cstr_greater_equal),\
    UT_CASE(test__algo_equal_range_if___cstr_all_less_equal),\
    UT_CASE(test__algo_equal_range_if___cstr_all_less),\
    UT_CASE_BEGIN(_algo_binary_search, test__algo_binary_search__invalid_range),\
    UT_CASE(test__algo_binary_search__invalid_range2),\
    UT_CASE(test__algo_binary_search__invalid_range3),\
    UT_CASE(test__algo_binary_search__empty),\
    UT_CASE(test__algo_binary_search__true),\
    UT_CASE(test__algo_binary_search__false),\
    UT_CASE(test__algo_binary_search__cstr_true),\
    UT_CASE(test__algo_binary_search__cstr_false),\
    UT_CASE_BEGIN(_algo_binary_search_if, test__algo_binary_search_if__invalid_range),\
    UT_CASE(test__algo_binary_search_if__invalid_range2),\
    UT_CASE(test__algo_binary_search_if__invalid_range3),\
    UT_CASE(test__algo_binary_search_if__empty),\
    UT_CASE(test__algo_binary_search_if__bfun_NULL_true),\
    UT_CASE(test__algo_binary_search_if__bfun_NULL_false),\
    UT_CASE(test__algo_binary_search_if__bfun_NULL_cstr_true),\
    UT_CASE(test__algo_binary_search_if__bfun_NULL_cstr_false),\
    UT_CASE(test__algo_binary_search_if__true),\
    UT_CASE(test__algo_binary_search_if__false),\
    UT_CASE(test__algo_binary_search_if__cstr_true),\
    UT_CASE(test__algo_binary_search_if__cstr_false)

#endif /* _UT_CSTL_ALGO_SORTING_PRIVATE_H_ */

