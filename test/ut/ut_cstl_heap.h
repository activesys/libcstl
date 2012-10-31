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
/*
 * test algo_is_heap
 */
UT_CASE_DECLARATION(algo_is_heap)
void test_algo_is_heap__invalid_range(void** state);
void test_algo_is_heap__invalid_range2(void** state);
void test_algo_is_heap__invalid_range3(void** state);
void test_algo_is_heap__empty(void** state);
void test_algo_is_heap__one(void** state);
void test_algo_is_heap__true(void** state);
void test_algo_is_heap__false(void** state);
void test_algo_is_heap__all_equal(void** state);
/*
 * test algo_is_heap_if
 */
UT_CASE_DECLARATION(algo_is_heap_if)
void test_algo_is_heap_if__invalid_range(void** state);
void test_algo_is_heap_if__invalid_range2(void** state);
void test_algo_is_heap_if__invalid_range3(void** state);
void test_algo_is_heap_if__empty(void** state);
void test_algo_is_heap_if__one(void** state);
void test_algo_is_heap_if__bfun_NULL_true(void** state);
void test_algo_is_heap_if__bfun_NULL_false(void** state);
void test_algo_is_heap_if__bfun_NULL_all_equal(void** state);
void test_algo_is_heap_if__true(void** state);
void test_algo_is_heap_if__false(void** state);
void test_algo_is_heap_if__all_equal(void** state);
/*
 * test algo_push_heap
 */
UT_CASE_DECLARATION(algo_push_heap)
void test_algo_push_heap__invalid_range(void** state);
void test_algo_push_heap__invalid_range2(void** state);
void test_algo_push_heap__invalid_range3(void** state);
void test_algo_push_heap__empty(void** state);
void test_algo_push_heap__one(void** state);
void test_algo_push_heap__two(void** state);
void test_algo_push_heap__three(void** state);
void test_algo_push_heap__more(void** state);
/*
 * test algo_push_heap_if
 */
UT_CASE_DECLARATION(algo_push_heap_if)
void test_algo_push_heap_if__invalid_range(void** state);
void test_algo_push_heap_if__invalid_range2(void** state);
void test_algo_push_heap_if__invalid_range3(void** state);
void test_algo_push_heap_if__empty(void** state);
void test_algo_push_heap_if__one(void** state);
void test_algo_push_heap_if__bfun_NULL_two(void** state);
void test_algo_push_heap_if__bfun_NULL_three(void** state);
void test_algo_push_heap_if__bfun_NULL_more(void** state);
void test_algo_push_heap_if__two(void** state);
void test_algo_push_heap_if__three(void** state);
void test_algo_push_heap_if__more(void** state);
/*
 * test algo_pop_heap
 */
UT_CASE_DECLARATION(algo_pop_heap)
void test_algo_pop_heap__invalid_range(void** state);
void test_algo_pop_heap__invalid_range2(void** state);
void test_algo_pop_heap__invalid_range3(void** state);
void test_algo_pop_heap__empty(void** state);
void test_algo_pop_heap__one(void** state);
void test_algo_pop_heap__two(void** state);
void test_algo_pop_heap__three(void** state);
void test_algo_pop_heap__more(void** state);
/*
 * test algo_pop_heap_if
 */
UT_CASE_DECLARATION(algo_pop_heap_if)
void test_algo_pop_heap_if__invalid_range(void** state);
void test_algo_pop_heap_if__invalid_range2(void** state);
void test_algo_pop_heap_if__invalid_range3(void** state);
void test_algo_pop_heap_if__empty(void** state);
void test_algo_pop_heap_if__one(void** state);
void test_algo_pop_heap_if__bfun_NULL_two(void** state);
void test_algo_pop_heap_if__bfun_NULL_three(void** state);
void test_algo_pop_heap_if__bfun_NULL_more(void** state);
void test_algo_pop_heap_if__two(void** state);
void test_algo_pop_heap_if__three(void** state);
void test_algo_pop_heap_if__more(void** state);
/*
 * test algo_sort_heap
 */
UT_CASE_DECLARATION(algo_sort_heap)
void test_algo_sort_heap__invalid_range(void** state);
void test_algo_sort_heap__invalid_range2(void** state);
void test_algo_sort_heap__invalid_range3(void** state);
void test_algo_sort_heap__empty(void** state);
void test_algo_sort_heap__one(void** state);
void test_algo_sort_heap__two(void** state);
void test_algo_sort_heap__three(void** state);
void test_algo_sort_heap__more(void** state);

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
    UT_CASE(test_algo_make_heap_if__not_heap),\
    UT_CASE_BEGIN(algo_is_heap, test_algo_is_heap__invalid_range),\
    UT_CASE(test_algo_is_heap__invalid_range2),\
    UT_CASE(test_algo_is_heap__invalid_range3),\
    UT_CASE(test_algo_is_heap__empty),\
    UT_CASE(test_algo_is_heap__one),\
    UT_CASE(test_algo_is_heap__true),\
    UT_CASE(test_algo_is_heap__false),\
    UT_CASE(test_algo_is_heap__all_equal),\
    UT_CASE_BEGIN(algo_is_heap_if, test_algo_is_heap_if__invalid_range),\
    UT_CASE(test_algo_is_heap_if__invalid_range2),\
    UT_CASE(test_algo_is_heap_if__invalid_range3),\
    UT_CASE(test_algo_is_heap_if__empty),\
    UT_CASE(test_algo_is_heap_if__one),\
    UT_CASE(test_algo_is_heap_if__bfun_NULL_true),\
    UT_CASE(test_algo_is_heap_if__bfun_NULL_false),\
    UT_CASE(test_algo_is_heap_if__bfun_NULL_all_equal),\
    UT_CASE(test_algo_is_heap_if__true),\
    UT_CASE(test_algo_is_heap_if__false),\
    UT_CASE(test_algo_is_heap_if__all_equal),\
    UT_CASE_BEGIN(algo_push_heap, test_algo_push_heap__invalid_range),\
    UT_CASE(test_algo_push_heap__invalid_range2),\
    UT_CASE(test_algo_push_heap__invalid_range3),\
    UT_CASE(test_algo_push_heap__empty),\
    UT_CASE(test_algo_push_heap__one),\
    UT_CASE(test_algo_push_heap__two),\
    UT_CASE(test_algo_push_heap__three),\
    UT_CASE(test_algo_push_heap__more),\
    UT_CASE_BEGIN(algo_push_heap_if, test_algo_push_heap_if__invalid_range),\
    UT_CASE(test_algo_push_heap_if__invalid_range2),\
    UT_CASE(test_algo_push_heap_if__invalid_range3),\
    UT_CASE(test_algo_push_heap_if__empty),\
    UT_CASE(test_algo_push_heap_if__one),\
    UT_CASE(test_algo_push_heap_if__bfun_NULL_two),\
    UT_CASE(test_algo_push_heap_if__bfun_NULL_three),\
    UT_CASE(test_algo_push_heap_if__bfun_NULL_more),\
    UT_CASE(test_algo_push_heap_if__two),\
    UT_CASE(test_algo_push_heap_if__three),\
    UT_CASE(test_algo_push_heap_if__more),\
    UT_CASE_BEGIN(algo_pop_heap, test_algo_pop_heap__invalid_range),\
    UT_CASE(test_algo_pop_heap__invalid_range2),\
    UT_CASE(test_algo_pop_heap__invalid_range3),\
    UT_CASE(test_algo_pop_heap__empty),\
    UT_CASE(test_algo_pop_heap__one),\
    UT_CASE(test_algo_pop_heap__two),\
    UT_CASE(test_algo_pop_heap__three),\
    UT_CASE(test_algo_pop_heap__more),\
    UT_CASE_BEGIN(algo_pop_heap_if, test_algo_pop_heap_if__invalid_range),\
    UT_CASE(test_algo_pop_heap_if__invalid_range2),\
    UT_CASE(test_algo_pop_heap_if__invalid_range3),\
    UT_CASE(test_algo_pop_heap_if__empty),\
    UT_CASE(test_algo_pop_heap_if__one),\
    UT_CASE(test_algo_pop_heap_if__bfun_NULL_two),\
    UT_CASE(test_algo_pop_heap_if__bfun_NULL_three),\
    UT_CASE(test_algo_pop_heap_if__bfun_NULL_more),\
    UT_CASE(test_algo_pop_heap_if__two),\
    UT_CASE(test_algo_pop_heap_if__three),\
    UT_CASE(test_algo_pop_heap_if__more),\
    UT_CASE_BEGIN(algo_sort_heap, test_algo_sort_heap__invalid_range),\
    UT_CASE(test_algo_sort_heap__invalid_range2),\
    UT_CASE(test_algo_sort_heap__invalid_range3),\
    UT_CASE(test_algo_sort_heap__empty),\
    UT_CASE(test_algo_sort_heap__one),\
    UT_CASE(test_algo_sort_heap__two),\
    UT_CASE(test_algo_sort_heap__three),\
    UT_CASE(test_algo_sort_heap__more)

#endif /* _UT_CSTL_HEAP_H_ */

