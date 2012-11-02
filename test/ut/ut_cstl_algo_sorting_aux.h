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
/*
 * test _algo_insertion_sort_if
 */
UT_CASE_DECLARATION(_algo_insertion_sort_if)
void test__algo_insertion_sort_if__invalid_range(void** state);
void test__algo_insertion_sort_if__invalid_range2(void** state);
void test__algo_insertion_sort_if__invalid_range3(void** state);
void test__algo_insertion_sort_if__bfun_NULL(void** state);
void test__algo_insertion_sort_if__value_NULL(void** state);
void test__algo_insertion_sort_if__empty(void** state);
void test__algo_insertion_sort_if__one(void** state);
void test__algo_insertion_sort_if__normal(void** state);
void test__algo_insertion_sort_if__duplicate(void** state);
void test__algo_insertion_sort_if__equal(void** state);
void test__algo_insertion_sort_if__sorted(void** state);
void test__algo_insertion_sort_if__cstr_normal(void** state);
void test__algo_insertion_sort_if__cstr_duplicate(void** state);
void test__algo_insertion_sort_if__cstr_equal(void** state);
void test__algo_insertion_sort_if__cstr_sorted(void** state);
/*
 * test _algo_intro_sort_if
 */
UT_CASE_DECLARATION(_algo_intro_sort_if)
void test__algo_intro_sort_if__invalid_range(void** state);
void test__algo_intro_sort_if__invalid_range2(void** state);
void test__algo_intro_sort_if__invalid_range3(void** state);
void test__algo_intro_sort_if__bfun_NULL(void** state);
void test__algo_intro_sort_if__value_NULL(void** state);
void test__algo_intro_sort_if__depth_0(void** state);
void test__algo_intro_sort_if__empty(void** state);
void test__algo_intro_sort_if__one(void** state);
void test__algo_intro_sort_if__normal(void** state);
void test__algo_intro_sort_if__equal(void** state);
void test__algo_intro_sort_if__duplicate(void** state);
void test__algo_intro_sort_if__sorted(void** state);
void test__algo_intro_sort_if__cstr_normal(void** state);
void test__algo_intro_sort_if__cstr_duplicate(void** state);
void test__algo_intro_sort_if__cstr_equal(void** state);
void test__algo_intro_sort_if__cstr_sorted(void** state);

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
    UT_CASE(test__algo_median_of_three_if__last_less_middle_less_first),\
    UT_CASE_BEGIN(_algo_insertion_sort_if, test__algo_insertion_sort_if__invalid_range),\
    UT_CASE(test__algo_insertion_sort_if__invalid_range2),\
    UT_CASE(test__algo_insertion_sort_if__invalid_range3),\
    UT_CASE(test__algo_insertion_sort_if__bfun_NULL),\
    UT_CASE(test__algo_insertion_sort_if__value_NULL),\
    UT_CASE(test__algo_insertion_sort_if__empty),\
    UT_CASE(test__algo_insertion_sort_if__one),\
    UT_CASE(test__algo_insertion_sort_if__normal),\
    UT_CASE(test__algo_insertion_sort_if__duplicate),\
    UT_CASE(test__algo_insertion_sort_if__equal),\
    UT_CASE(test__algo_insertion_sort_if__sorted),\
    UT_CASE(test__algo_insertion_sort_if__cstr_normal),\
    UT_CASE(test__algo_insertion_sort_if__cstr_duplicate),\
    UT_CASE(test__algo_insertion_sort_if__cstr_equal),\
    UT_CASE(test__algo_insertion_sort_if__cstr_sorted),\
    UT_CASE_BEGIN(_algo_intro_sort_if, test__algo_intro_sort_if__invalid_range),\
    UT_CASE(test__algo_intro_sort_if__invalid_range2),\
    UT_CASE(test__algo_intro_sort_if__invalid_range3),\
    UT_CASE(test__algo_intro_sort_if__bfun_NULL),\
    UT_CASE(test__algo_intro_sort_if__value_NULL),\
    UT_CASE(test__algo_intro_sort_if__depth_0),\
    UT_CASE(test__algo_intro_sort_if__empty),\
    UT_CASE(test__algo_intro_sort_if__one),\
    UT_CASE(test__algo_intro_sort_if__normal),\
    UT_CASE(test__algo_intro_sort_if__duplicate),\
    UT_CASE(test__algo_intro_sort_if__equal),\
    UT_CASE(test__algo_intro_sort_if__sorted),\
    UT_CASE(test__algo_intro_sort_if__cstr_normal),\
    UT_CASE(test__algo_intro_sort_if__cstr_duplicate),\
    UT_CASE(test__algo_intro_sort_if__cstr_equal),\
    UT_CASE(test__algo_intro_sort_if__cstr_sorted)

#endif /* _UT_CSTL_ALGO_SORTING_AUX_H_ */

