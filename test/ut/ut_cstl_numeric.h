#ifndef _UT_CSTL_NUMERIC_H_
#define _UT_CSTL_NUMERIC_H_

UT_SUIT_DECLARATION(cstl_numeric)

/*
 * test algo_partial_sum
 */
UT_CASE_DECLARATION(algo_partial_sum)
void test_algo_partial_sum__invalid_first_range(void** state);
void test_algo_partial_sum__invalid_second_range(void** state);
void test_algo_partial_sum__not_same_type(void** state);
void test_algo_partial_sum__empty(void** state);
void test_algo_partial_sum__not_empty(void** state);
/*
 * test algo_partial_sum_if
 */
UT_CASE_DECLARATION(algo_partial_sum_if)
void test_algo_partial_sum_if__invalid_first_range(void** state);
void test_algo_partial_sum_if__invalid_second_range(void** state);
void test_algo_partial_sum_if__not_same_type(void** state);
void test_algo_partial_sum_if__empty(void** state);
void test_algo_partial_sum_if__bfun_NULL_not_empty(void** state);
void test_algo_partial_sum_if__not_empty(void** state);
/*
 * test algo_adjacent_difference
 */
UT_CASE_DECLARATION(algo_adjacent_difference)
void test_algo_adjacent_difference__invalid_first_range(void** state);
void test_algo_adjacent_difference__invalid_second_range(void** state);
void test_algo_adjacent_difference__not_same_type(void** state);
void test_algo_adjacent_difference__empty(void** state);
void test_algo_adjacent_difference__not_empty(void** state);
/*
 * test algo_adjacent_difference_if
 */
UT_CASE_DECLARATION(algo_adjacent_difference_if)
void test_algo_adjacent_difference_if__invalid_first_range(void** state);
void test_algo_adjacent_difference_if__invalid_second_range(void** state);
void test_algo_adjacent_difference_if__not_same_type(void** state);
void test_algo_adjacent_difference_if__empty(void** state);
void test_algo_adjacent_difference_if__bfun_NULL_not_empty(void** state);
void test_algo_adjacent_difference_if__not_empty(void** state);
/*
 * test algo_power
 */
UT_CASE_DECLARATION(algo_power)
void test_algo_power__invalid_iterator(void** state);
void test_algo_power__output_NULL(void** state);
void test_algo_power__normal(void** state);
/*
 * test algo_power_if
 */
UT_CASE_DECLARATION(algo_power_if)
void test_algo_power_if__invalid_iterator(void** state);
void test_algo_power_if__output_NULL(void** state);
void test_algo_power_if__bfun_NULL_normal(void** state);
void test_algo_power_if__normal(void** state);

#define UT_CSTL_NUMERIC_CASE\
    UT_SUIT_BEGIN(cstl_numeric, test_algo_partial_sum__invalid_first_range),\
    UT_CASE(test_algo_partial_sum__invalid_second_range),\
    UT_CASE(test_algo_partial_sum__not_same_type),\
    UT_CASE(test_algo_partial_sum__empty),\
    UT_CASE(test_algo_partial_sum__not_empty),\
    UT_CASE_BEGIN(algo_partial_sum_if, test_algo_partial_sum_if__invalid_first_range),\
    UT_CASE(test_algo_partial_sum_if__invalid_second_range),\
    UT_CASE(test_algo_partial_sum_if__not_same_type),\
    UT_CASE(test_algo_partial_sum_if__empty),\
    UT_CASE(test_algo_partial_sum_if__bfun_NULL_not_empty),\
    UT_CASE(test_algo_partial_sum_if__not_empty),\
    UT_CASE_BEGIN(algo_adjacent_difference, test_algo_adjacent_difference__invalid_first_range),\
    UT_CASE(test_algo_adjacent_difference__invalid_second_range),\
    UT_CASE(test_algo_adjacent_difference__not_same_type),\
    UT_CASE(test_algo_adjacent_difference__empty),\
    UT_CASE(test_algo_adjacent_difference__not_empty),\
    UT_CASE_BEGIN(algo_adjacent_difference_if, test_algo_adjacent_difference_if__invalid_first_range),\
    UT_CASE(test_algo_adjacent_difference_if__invalid_second_range),\
    UT_CASE(test_algo_adjacent_difference_if__not_same_type),\
    UT_CASE(test_algo_adjacent_difference_if__empty),\
    UT_CASE(test_algo_adjacent_difference_if__bfun_NULL_not_empty),\
    UT_CASE(test_algo_adjacent_difference_if__not_empty),\
    UT_CASE_BEGIN(algo_power, test_algo_power__invalid_iterator),\
    UT_CASE(test_algo_power__output_NULL),\
    UT_CASE(test_algo_power__normal),\
    UT_CASE_BEGIN(algo_power_if, test_algo_power_if__invalid_iterator),\
    UT_CASE(test_algo_power_if__output_NULL),\
    UT_CASE(test_algo_power_if__bfun_NULL_normal),\
    UT_CASE(test_algo_power_if__normal)

#endif /* _UT_CSTL_NUMERIC_H_ */

