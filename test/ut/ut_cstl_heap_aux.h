#ifndef _UT_CSTL_HEAP_AUX_H_
#define _UT_CSTL_HEAP_AUX_H_

UT_SUIT_DECLARATION(cstl_heap_aux)

/*
 * test _algo_adjust_heap
 */
UT_CASE_DECLARATION(_algo_adjust_heap)
void test__algo_adjust_heap__invalid_range(void** state);
void test__algo_adjust_heap__invalid_range2(void** state);
void test__algo_adjust_heap__invalid_range3(void** state);
void test__algo_adjust_heap__invalid_parent(void** state);
void test__algo_adjust_heap__empty(void** state);
void test__algo_adjust_heap__one(void** state);
void test__algo_adjust_heap__two1(void** state);
void test__algo_adjust_heap__two2(void** state);
void test__algo_adjust_heap__three1(void** state);
void test__algo_adjust_heap__three2(void** state);
void test__algo_adjust_heap__three3(void** state);
void test__algo_adjust_heap__three4(void** state);

#define UT_CSTL_HEAP_AUX_CASE\
    UT_SUIT_BEGIN(cstl_heap_aux, test__algo_adjust_heap__invalid_range),\
    UT_CASE(test__algo_adjust_heap__invalid_range2),\
    UT_CASE(test__algo_adjust_heap__invalid_range3),\
    UT_CASE(test__algo_adjust_heap__invalid_parent),\
    UT_CASE(test__algo_adjust_heap__empty),\
    UT_CASE(test__algo_adjust_heap__one),\
    UT_CASE(test__algo_adjust_heap__two1),\
    UT_CASE(test__algo_adjust_heap__two2),\
    UT_CASE(test__algo_adjust_heap__three1),\
    UT_CASE(test__algo_adjust_heap__three2),\
    UT_CASE(test__algo_adjust_heap__three3),\
    UT_CASE(test__algo_adjust_heap__three4)

#endif /* _UT_CSTL_HEAP_AUX_H_ */

