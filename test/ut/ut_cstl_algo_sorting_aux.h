#ifndef _UT_CSTL_ALGO_SORTING_AUX_H_
#define _UT_CSTL_ALGO_SORTING_AUX_H_

UT_SUIT_DECLARATION(cstl_algo_sorting_aux)

/*
 * test _algo_lg
 */
UT_CASE_DECLARATION(_algo_lg)
void test__algo_lg__0(void** state);
void test__algo_lg__1(void** state);
void test__algo_lg__2_power_n(void** state);
void test__algo_lg__not_2_power_n(void** state);
/*
 * test _algo_median_of_three_if
 */
UT_CASE_DECLARATION(_algo_median_of_three_if)
void test__algo_median_of_three_if__invalid_first(void** state);
void test__algo_median_of_three_if__invalid_middle(void** state);
void test__algo_median_of_three_if__invalid_last(void** state);
void test__algo_median_of_three_if__bfun_NULL(void** state);
void test__algo_median_of_three_if__first_less_middle_less_last(void** state);
void test__algo_median_of_three_if__first_less_middle_equal_last(void** state);
void test__algo_median_of_three_if__first_equal_middle_less_last(void** state);
void test__algo_median_of_three_if__first_equal_middle_equal_last(void** state);
void test__algo_median_of_three_if__middle_less_first_less_last(void** state);
void test__algo_median_of_three_if__middle_less_first_equal_last(void** state);
void test__algo_median_of_three_if__last_less_first_less_middle(void** state);
void test__algo_median_of_three_if__last_less_first_equal_middle(void** state);
void test__algo_median_of_three_if__last_equal_first_less_middle(void** state);
void test__algo_median_of_three_if__first_less_last_less_middle(void** state);
void test__algo_median_of_three_if__middle_less_last_less_first(void** state);
void test__algo_median_of_three_if__middle_equal_last_less_first(void** state);
void test__algo_median_of_three_if__last_less_middle_less_first(void** state);

#define UT_CSTL_ALGO_SORTING_AUX_CASE\
    UT_SUIT_BEGIN(cstl_algo_sorting_aux, test__algo_lg__0),\
    UT_CASE(test__algo_lg__1),\
    UT_CASE(test__algo_lg__2_power_n),\
    UT_CASE(test__algo_lg__not_2_power_n),\
    UT_CASE_BEGIN(_algo_median_of_three_if, test__algo_median_of_three_if__invalid_first),\
    UT_CASE(test__algo_median_of_three_if__invalid_middle),\
    UT_CASE(test__algo_median_of_three_if__invalid_last),\
    UT_CASE(test__algo_median_of_three_if__bfun_NULL),\
    UT_CASE(test__algo_median_of_three_if__first_less_middle_less_last),\
    UT_CASE(test__algo_median_of_three_if__first_less_middle_equal_last),\
    UT_CASE(test__algo_median_of_three_if__first_equal_middle_less_last),\
    UT_CASE(test__algo_median_of_three_if__first_equal_middle_equal_last),\
    UT_CASE(test__algo_median_of_three_if__middle_less_first_less_last),\
    UT_CASE(test__algo_median_of_three_if__middle_less_first_equal_last),\
    UT_CASE(test__algo_median_of_three_if__last_less_first_less_middle),\
    UT_CASE(test__algo_median_of_three_if__last_less_first_equal_middle),\
    UT_CASE(test__algo_median_of_three_if__last_equal_first_less_middle),\
    UT_CASE(test__algo_median_of_three_if__first_less_last_less_middle),\
    UT_CASE(test__algo_median_of_three_if__middle_less_last_less_first),\
    UT_CASE(test__algo_median_of_three_if__middle_equal_last_less_first),\
    UT_CASE(test__algo_median_of_three_if__last_less_middle_less_first)

#endif /* _UT_CSTL_ALGO_SORTING_AUX_H_ */

