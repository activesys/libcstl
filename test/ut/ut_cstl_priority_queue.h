#ifndef _UT_CSTL_PRIORITY_QUEUE_H_
#define _UT_CSTL_PRIORITY_QUEUE_H_

UT_SUIT_DECLARATION(cstl_priority_queue)

/*
 * test priority_queue_init
 */
UT_CASE_DECLARATION(priority_queue_init)
void test_priority_queue_init__null(void** state);
void test_priority_queue_init__successfully(void** state);
/*
 * test priority_queue_init_ex
 */
UT_CASE_DECLARATION(priority_queue_init_ex)
void test_priority_queue_init_ex__null(void** state);
void test_priority_queue_init_ex__bfun_NULL(void** state);
void test_priority_queue_init_ex__successfully(void** state);
/*
 * test priority_queue_destroy
 */
UT_CASE_DECLARATION(priority_queue_destroy)
void test_priority_queue_destroy__null(void** state);
void test_priority_queue_destroy__not_init(void** state);
void test_priority_queue_destroy__empty(void** state);
void test_priority_queue_destroy__not_empty(void** state);
/*
 * test priority_queue_init_copy
 */
UT_CASE_DECLARATION(priority_queue_init_copy)
void test_priority_queue_init_copy__dest_NULL(void** state);
void test_priority_queue_init_copy__src_NULL(void** state);
void test_priority_queue_init_copy__src_not_init(void** state);
void test_priority_queue_init_copy__not_same_type(void** state);
void test_priority_queue_init_copy__bfun_NULL(void** state);
void test_priority_queue_init_copy__bfun_not_NULL(void** state);
/*
 * test priority_queue_init_copy_range
 */
UT_CASE_DECLARATION(priority_queue_init_copy_range)
void test_priority_queue_init_copy_range__dest_NULL(void** state);
void test_priority_queue_init_copy_range__invalid_range(void** state);
void test_priority_queue_init_copy_range__not_same_type(void** state);
void test_priority_queue_init_copy_range__empty(void** state);
void test_priority_queue_init_copy_range__not_empty(void** state);
/*
 * test priority_queue_init_copy_range_ex
 */
UT_CASE_DECLARATION(priority_queue_init_copy_range_ex)
void test_priority_queue_init_copy_range_ex__dest_NULL(void** state);
void test_priority_queue_init_copy_range_ex__invalid_range(void** state);
void test_priority_queue_init_copy_range_ex__not_same_type(void** state);
void test_priority_queue_init_copy_range_ex__empty(void** state);
void test_priority_queue_init_copy_range_ex__bfun_NULL_not_empty(void** state);
void test_priority_queue_init_copy_range_ex__not_empty(void** state);
/*
 * test priority_queue_assign
 */
UT_CASE_DECLARATION(priority_queue_assign)
void test_priority_queue_assign__dest_NULL(void** state);
void test_priority_queue_assign__src_NULL(void** state);
void test_priority_queue_assign__dest_not_init(void** state);
void test_priority_queue_assign__src_not_init(void** state);
void test_priority_queue_assign__not_same_type(void** state);
void test_priority_queue_assign__not_same_rule(void** state);
void test_priority_queue_assign__empty(void** state);
void test_priority_queue_assign__not_empty(void** state);
/*
 * test priority_queue_empty
 */
UT_CASE_DECLARATION(priority_queue_empty)
void test_priority_queue_empty__NULL(void** state);
void test_priority_queue_empty__not_init(void** state);
void test_priority_queue_empty__empty(void** state);
void test_priority_queue_empty__not_empty(void** state);
/*
 * test priority_queue_size
 */
UT_CASE_DECLARATION(priority_queue_size)
void test_priority_queue_size__NULL(void** state);
void test_priority_queue_size__not_init(void** state);
void test_priority_queue_size__empty(void** state);
void test_priority_queue_size__not_empty(void** state);
/*
 * test priority_queue_top
 */
UT_CASE_DECLARATION(priority_queue_top)
void test_priority_queue_top__NULL(void** state);
void test_priority_queue_top__not_init(void** state);
void test_priority_queue_top__empty(void** state);
void test_priority_queue_top__not_empty(void** state);
/*
 * test priority_queue_pop
 */
UT_CASE_DECLARATION(priority_queue_pop)
void test_priority_queue_pop__NULL(void** state);
void test_priority_queue_pop__not_init(void** state);
void test_priority_queue_pop__empty(void** state);
void test_priority_queue_pop__not_empty(void** state);
void test_priority_queue_pop__not_empty_ex(void** state);
/*
 * test priority_queue_init_copy_array
 */
UT_CASE_DECLARATION(priority_queue_init_copy_array)
void test_priority_queue_init_copy_array__dest_null(void** state);
void test_priority_queue_init_copy_array__src_null(void** state);
void test_priority_queue_init_copy_array__empty(void** state);
void test_priority_queue_init_copy_array__not_empty(void** state);
/*
 * test priority_queue_init_copy_array_ex
 */
UT_CASE_DECLARATION(priority_queue_init_copy_array_ex)
void test_priority_queue_init_copy_array_ex__dest_null(void** state);
void test_priority_queue_init_copy_array_ex__src_null(void** state);
void test_priority_queue_init_copy_array_ex__empty(void** state);
void test_priority_queue_init_copy_array_ex__not_empty(void** state);
void test_priority_queue_init_copy_array_ex__empty_bfun_NULL(void** state);
void test_priority_queue_init_copy_array_ex__not_empty_bfun_NULL(void** state);

#define UT_CSTL_PRIORITY_QUEUE_CASE\
    UT_SUIT_BEGIN(cstl_priority_queue, test_priority_queue_init__null),\
    UT_CASE(test_priority_queue_init__successfully),\
    UT_CASE_BEGIN(priority_queue_init_ex, test_priority_queue_init_ex__null),\
    UT_CASE(test_priority_queue_init_ex__bfun_NULL),\
    UT_CASE(test_priority_queue_init_ex__successfully),\
    UT_CASE_BEGIN(priority_queue_destroy, test_priority_queue_destroy__null),\
    UT_CASE(test_priority_queue_destroy__not_init),\
    UT_CASE(test_priority_queue_destroy__empty),\
    UT_CASE(test_priority_queue_destroy__not_empty),\
    UT_CASE_BEGIN(priority_queue_init_copy, test_priority_queue_init_copy__dest_NULL),\
    UT_CASE(test_priority_queue_init_copy__src_NULL),\
    UT_CASE(test_priority_queue_init_copy__src_not_init),\
    UT_CASE(test_priority_queue_init_copy__not_same_type),\
    UT_CASE(test_priority_queue_init_copy__bfun_NULL),\
    UT_CASE(test_priority_queue_init_copy__bfun_not_NULL),\
    UT_CASE_BEGIN(priority_queue_init_copy_range, test_priority_queue_init_copy_range__dest_NULL),\
    UT_CASE(test_priority_queue_init_copy_range__invalid_range),\
    UT_CASE(test_priority_queue_init_copy_range__not_same_type),\
    UT_CASE(test_priority_queue_init_copy_range__empty),\
    UT_CASE(test_priority_queue_init_copy_range__not_empty),\
    UT_CASE_BEGIN(priority_queue_init_copy_range_ex, test_priority_queue_init_copy_range_ex__dest_NULL),\
    UT_CASE(test_priority_queue_init_copy_range_ex__invalid_range),\
    UT_CASE(test_priority_queue_init_copy_range_ex__not_same_type),\
    UT_CASE(test_priority_queue_init_copy_range_ex__empty),\
    UT_CASE(test_priority_queue_init_copy_range_ex__bfun_NULL_not_empty),\
    UT_CASE(test_priority_queue_init_copy_range_ex__not_empty),\
    UT_CASE_BEGIN(priority_queue_assign, test_priority_queue_assign__dest_NULL),\
    UT_CASE(test_priority_queue_assign__src_NULL),\
    UT_CASE(test_priority_queue_assign__dest_not_init),\
    UT_CASE(test_priority_queue_assign__src_not_init),\
    UT_CASE(test_priority_queue_assign__not_same_type),\
    UT_CASE(test_priority_queue_assign__not_same_rule),\
    UT_CASE(test_priority_queue_assign__empty),\
    UT_CASE(test_priority_queue_assign__not_empty),\
    UT_CASE_BEGIN(priority_queue_empty, test_priority_queue_empty__NULL),\
    UT_CASE(test_priority_queue_empty__not_init),\
    UT_CASE(test_priority_queue_empty__empty),\
    UT_CASE(test_priority_queue_empty__not_empty),\
    UT_CASE_BEGIN(priority_queue_size, test_priority_queue_size__NULL),\
    UT_CASE(test_priority_queue_size__not_init),\
    UT_CASE(test_priority_queue_size__empty),\
    UT_CASE(test_priority_queue_size__not_empty),\
    UT_CASE_BEGIN(priority_queue_top, test_priority_queue_top__NULL),\
    UT_CASE(test_priority_queue_top__not_init),\
    UT_CASE(test_priority_queue_top__empty),\
    UT_CASE(test_priority_queue_top__not_empty),\
    UT_CASE_BEGIN(priority_queue_pop, test_priority_queue_pop__NULL),\
    UT_CASE(test_priority_queue_pop__not_init),\
    UT_CASE(test_priority_queue_pop__empty),\
    UT_CASE(test_priority_queue_pop__not_empty),\
    UT_CASE(test_priority_queue_pop__not_empty_ex),\
    UT_CASE_BEGIN(priority_queue_init_copy_array, test_priority_queue_init_copy_array__dest_null),\
    UT_CASE(test_priority_queue_init_copy_array__src_null),\
    UT_CASE(test_priority_queue_init_copy_array__empty),\
    UT_CASE(test_priority_queue_init_copy_array__not_empty),\
    UT_CASE_BEGIN(priority_queue_init_copy_array_ex, test_priority_queue_init_copy_array_ex__dest_null),\
    UT_CASE(test_priority_queue_init_copy_array_ex__src_null),\
    UT_CASE(test_priority_queue_init_copy_array_ex__empty),\
    UT_CASE(test_priority_queue_init_copy_array_ex__not_empty),\
    UT_CASE(test_priority_queue_init_copy_array_ex__empty_bfun_NULL),\
    UT_CASE(test_priority_queue_init_copy_array_ex__not_empty_bfun_NULL)

#endif /* _UT_CSTL_PRIORITY_QUEUE_H_ */

