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
    UT_CASE(test_priority_queue_init_copy_range_ex__not_empty)

#endif /* _UT_CSTL_PRIORITY_QUEUE_H_ */

