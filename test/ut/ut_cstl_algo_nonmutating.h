#ifndef _UT_CSTL_ALGO_NONMUTATING_H_
#define _UT_CSTL_ALGO_NONMUTATING_H_

UT_SUIT_DECLARATION(cstl_algo_nonmutating)
/*
 * test algo_for_each
 */
UT_CASE_DECLARATION(algo_for_each)
void test_algo_for_each__invalid_range(void** state);
void test_algo_for_each__invalid_range_2(void** state);
void test_algo_for_each__empty_range(void** state);
void test_algo_for_each__ufun_NULL(void** state);
void test_algo_for_each__mutate_all(void** state);
void test_algo_for_each__mutate_partial(void** state);

#define UT_CSTL_ALGO_NONMUTATING_CASE\
	UT_SUIT_BEGIN(cstl_algo_nonmutating, test_algo_for_each__invalid_range),\
    UT_CASE(test_algo_for_each__invalid_range_2),\
    UT_CASE(test_algo_for_each__empty_range),\
    UT_CASE(test_algo_for_each__ufun_NULL),\
    UT_CASE(test_algo_for_each__mutate_all),\
    UT_CASE(test_algo_for_each__mutate_partial),\

#endif /* _UT_CSTL_ALGO_NONMUTATING_H_ */
