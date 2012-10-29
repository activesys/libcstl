#ifndef _UT_CSTL_HEAP_H_
#define _UT_CSTL_HEAP_H_

UT_SUIT_DECLARATION(cstl_heap)

/*
 * test algo_make_heap
 */
UT_CASE_DECLARATION(algo_make_heap)
void test_algo_make_heap__invalid_range(void** state);
void test_algo_make_heap__invalid_range2(void** state);
void test_algo_make_heap__invalid_range3(void** state);
void test_algo_make_heap__empty(void** state);
void test_algo_make_heap__one(void** state);
void test_algo_make_heap__is_heap(void** state);
void test_algo_make_heap__is_first_half_heap(void** state);
void test_algo_make_heap__is_second_half_heap(void** state);
void test_algo_make_heap__not_heap(void** state);
/*
 * test algo_make_heap_if
 */
UT_CASE_DECLARATION(algo_make_heap_if)
void test_algo_make_heap_if__invalid_range(void** state);
void test_algo_make_heap_if__invalid_range2(void** state);
void test_algo_make_heap_if__invalid_range3(void** state);
void test_algo_make_heap_if__bfun_NULL(void** state);
void test_algo_make_heap_if__empty(void** state);
void test_algo_make_heap_if__one(void** state);
void test_algo_make_heap_if__is_heap(void** state);
void test_algo_make_heap_if__is_first_half_heap(void** state);
void test_algo_make_heap_if__is_second_half_heap(void** state);
void test_algo_make_heap_if__not_heap(void** state);

#define UT_CSTL_HEAP_CASE\
    UT_SUIT_BEGIN(cstl_heap, test_algo_make_heap__invalid_range),\
    UT_CASE(test_algo_make_heap__invalid_range2),\
    UT_CASE(test_algo_make_heap__invalid_range3),\
    UT_CASE(test_algo_make_heap__empty),\
    UT_CASE(test_algo_make_heap__one),\
    UT_CASE(test_algo_make_heap__is_heap),\
    UT_CASE(test_algo_make_heap__is_first_half_heap),\
    UT_CASE(test_algo_make_heap__is_second_half_heap),\
    UT_CASE(test_algo_make_heap__not_heap),\
    UT_CASE_BEGIN(algo_make_heap_if, test_algo_make_heap_if__invalid_range),\
    UT_CASE(test_algo_make_heap_if__invalid_range2),\
    UT_CASE(test_algo_make_heap_if__invalid_range3),\
    UT_CASE(test_algo_make_heap_if__bfun_NULL),\
    UT_CASE(test_algo_make_heap_if__empty),\
    UT_CASE(test_algo_make_heap_if__one),\
    UT_CASE(test_algo_make_heap_if__is_heap),\
    UT_CASE(test_algo_make_heap_if__is_first_half_heap),\
    UT_CASE(test_algo_make_heap_if__is_second_half_heap),\
    UT_CASE(test_algo_make_heap_if__not_heap)

#endif /* _UT_CSTL_HEAP_H_ */

