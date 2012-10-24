#ifndef _UT_CSTL_ALGO_MUTATING_AUX_H_
#define _UT_CSTL_ALGO_MUTATING_AUX_H_

UT_SUIT_DECLARATION(cstl_algo_mutating_aux)

/*
 * test _algo_rotate_forward
 */
UT_CASE_DECLARATION(_algo_rotate_forward)
void test__algo_rotate_forward__invalid_first_range(void** state);
void test__algo_rotate_forward__invalid_first_range2(void** state);
void test__algo_rotate_forward__invalid_first_range3(void** state);
void test__algo_rotate_forward__invalid_second_range(void** state);
void test__algo_rotate_forward__invalid_second_range2(void** state);
void test__algo_rotate_forward__invalid_second_range3(void** state);
void test__algo_rotate_forward__first_less_than_second(void** state);
void test__algo_rotate_forward__first_equal_to_second(void** state);
void test__algo_rotate_forward__first_greater_than_second(void** state);

#define UT_CSTL_ALGO_MUTATING_AUX_CASE\
    UT_SUIT_BEGIN(cstl_algo_mutating_aux, test__algo_rotate_forward__invalid_first_range),\
    UT_CASE(test__algo_rotate_forward__invalid_first_range2),\
    UT_CASE(test__algo_rotate_forward__invalid_first_range3),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range2),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range3),\
    UT_CASE(test__algo_rotate_forward__first_less_than_second),\
    UT_CASE(test__algo_rotate_forward__first_equal_to_second),\
    UT_CASE(test__algo_rotate_forward__first_greater_than_second)

#endif /* _UT_CSTL_ALGO_MUTATING_AUX_H_ */

