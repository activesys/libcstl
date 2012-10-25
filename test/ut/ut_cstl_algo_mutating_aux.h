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
void test__algo_rotate_forward__empty(void** state);
void test__algo_rotate_forward__first_range_empty(void** state);
void test__algo_rotate_forward__second_range_empty(void** state);
/*
 * test _algo_partition_biditer
 */
UT_CASE_DECLARATION(_algo_partition_biditer)
void test__algo_partition_biditer__invalid_range(void** state);
void test__algo_partition_biditer__invalid_range2(void** state);
void test__algo_partition_biditer__invalid_range3(void** state);
void test__algo_partition_biditer__empty(void** state);
void test__algo_partition_biditer__ufun_NULL(void** state);
void test__algo_partition_biditer__all_satify(void** state);
void test__algo_partition_biditer__all_not_satify(void** state);
void test__algo_partition_biditer__normal(void** state);

#define UT_CSTL_ALGO_MUTATING_AUX_CASE\
    UT_SUIT_BEGIN(cstl_algo_mutating_aux, test__algo_rotate_forward__invalid_first_range),\
    UT_CASE(test__algo_rotate_forward__invalid_first_range2),\
    UT_CASE(test__algo_rotate_forward__invalid_first_range3),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range2),\
    UT_CASE(test__algo_rotate_forward__invalid_second_range3),\
    UT_CASE(test__algo_rotate_forward__first_less_than_second),\
    UT_CASE(test__algo_rotate_forward__first_equal_to_second),\
    UT_CASE(test__algo_rotate_forward__first_greater_than_second),\
    UT_CASE(test__algo_rotate_forward__empty),\
    UT_CASE(test__algo_rotate_forward__first_range_empty),\
    UT_CASE(test__algo_rotate_forward__second_range_empty),\
    UT_CASE_BEGIN(_algo_partition_biditer, test__algo_partition_biditer__invalid_range),\
    UT_CASE(test__algo_partition_biditer__invalid_range2),\
    UT_CASE(test__algo_partition_biditer__invalid_range3),\
    UT_CASE(test__algo_partition_biditer__empty),\
    UT_CASE(test__algo_partition_biditer__ufun_NULL),\
    UT_CASE(test__algo_partition_biditer__all_satify),\
    UT_CASE(test__algo_partition_biditer__all_not_satify),\
    UT_CASE(test__algo_partition_biditer__normal)

#endif /* _UT_CSTL_ALGO_MUTATING_AUX_H_ */

