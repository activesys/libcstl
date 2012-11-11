#ifndef _UT_CSTL_PRIORITY_QUEUE_PRIVATE_H_
#define _UT_CSTL_PRIORITY_QUEUE_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_priority_queue_private)

/*
 * test _create_priority_queue
 */
UT_CASE_DECLARATION(_create_priority_queue)
void test__create_priority_queue__null_typename(void** state);
void test__create_priority_queue__unregisted_type(void** state);
void test__create_priority_queue__c_builtin_type(void** state);
void test__create_priority_queue__libcstl_builtin_type(void** state);
void test__create_priority_queue__user_defined_type(void** state);
/*
 * test _create_priority_queue_auxiliary
 */
UT_CASE_DECLARATION(_create_priority_queue_auxiliary)
void test__create_priority_queue_auxiliary__null_priority_queue_adaptor(void** state);
void test__create_priority_queue_auxiliary__null_typename(void** state);
void test__create_priority_queue_auxiliary__unregisted_type(void** state);
void test__create_priority_queue_auxiliary__c_builtin(void** state);
void test__create_priority_queue_auxiliary__libcstl_builtin(void** state);
void test__create_priority_queue_auxiliary__user_defined(void** state);
void test__create_priority_queue_auxiliary__user_defined_dup(void** state);
/*
 * test _priority_queue_destroy_auxiliary
 */
UT_CASE_DECLARATION(_priority_queue_destroy_auxiliary)
void test__priority_queue_destroy_auxiliary__null_priority_queue_adaptor(void** state);
void test__priority_queue_destroy_auxiliary__non_created_priority_queue_adaptor(void** state);
void test__priority_queue_destroy_auxiliary__non_inited(void** state);
void test__priority_queue_destroy_auxiliary__empty(void** state);
void test__priority_queue_destroy_auxiliary__non_empty(void** state);
/*
 * test _priority_queue_push
 */
UT_CASE_DECLARATION(_priority_queue_push)
void test__priority_queue_push__null_priority_queue_adaptor(void** state);
void test__priority_queue_push__non_inited_priority_queue_adaptor(void** state);
void test__priority_queue_push__empty(void** state);
void test__priority_queue_push__non_empty(void** state);
void test__priority_queue_push__non_empty_multiple(void** state);

#define UT_CSTL_PRIORITY_QUEUE_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_priority_queue_private, test__create_priority_queue__null_typename),\
    UT_CASE(test__create_priority_queue__unregisted_type),\
    UT_CASE(test__create_priority_queue__c_builtin_type),\
    UT_CASE(test__create_priority_queue__libcstl_builtin_type),\
    UT_CASE(test__create_priority_queue__user_defined_type),\
    UT_CASE_BEGIN(_create_priority_queue_auxiliary, test__create_priority_queue_auxiliary__null_priority_queue_adaptor),\
    UT_CASE(test__create_priority_queue_auxiliary__null_typename),\
    UT_CASE(test__create_priority_queue_auxiliary__unregisted_type),\
    UT_CASE(test__create_priority_queue_auxiliary__c_builtin),\
    UT_CASE(test__create_priority_queue_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_priority_queue_auxiliary__user_defined),\
    UT_CASE(test__create_priority_queue_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_priority_queue_destroy_auxiliary, test__priority_queue_destroy_auxiliary__null_priority_queue_adaptor),\
    UT_CASE(test__priority_queue_destroy_auxiliary__non_created_priority_queue_adaptor),\
    UT_CASE(test__priority_queue_destroy_auxiliary__non_inited),\
    UT_CASE(test__priority_queue_destroy_auxiliary__empty),\
    UT_CASE(test__priority_queue_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_priority_queue_push, test__priority_queue_push__null_priority_queue_adaptor),\
    UT_CASE(test__priority_queue_push__non_inited_priority_queue_adaptor),\
    UT_CASE(test__priority_queue_push__empty),\
    UT_CASE(test__priority_queue_push__non_empty),\
    UT_CASE(test__priority_queue_push__non_empty_multiple)

#endif /* _UT_CSTL_PRIORITY_QUEUE_PRIVATE_H_ */

