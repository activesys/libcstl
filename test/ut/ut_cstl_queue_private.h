#ifndef _UT_CSTL_QUEUE_PRIVATE_H_
#define _UT_CSTL_QUEUE_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_queue_private)

/*
 * test _create_queue
 */
UT_CASE_DECLARATION(_create_queue)
void test__create_queue__null_typename(void** state);
void test__create_queue__unregisted_type(void** state);
void test__create_queue__c_builtin_type(void** state);
void test__create_queue__libcstl_builtin_type(void** state);
void test__create_queue__user_defined_type(void** state);
void test__create_queue__user_defined_type_dup(void** state);
/*
 * test _create_queue_auxiliary
 */
UT_CASE_DECLARATION(_create_queue_auxiliary)
void test__create_queue_auxiliary__null_queue_adaptor(void** state);
void test__create_queue_auxiliary__null_typename(void** state);
void test__create_queue_auxiliary__unregisted_type(void** state);
void test__create_queue_auxiliary__c_builtin(void** state);
void test__create_queue_auxiliary__libcstl_builtin(void** state);
void test__create_queue_auxiliary__user_defined(void** state);
void test__create_queue_auxiliary__user_defined_dup(void** state);
/*
 * test _queue_destroy_auxiliary
 */
UT_CASE_DECLARATION(_queue_destroy_auxiliary)
void test__queue_destroy_auxiliary__null_queue_adaptor(void** state);
void test__queue_destroy_auxiliary__non_created_queue_adaptor(void** state);
void test__queue_destroy_auxiliary__non_inited(void** state);
void test__queue_destroy_auxiliary__empty(void** state);
void test__queue_destroy_auxiliary__non_empty(void** state);
/*
 * test _queue_push and _queue_push_varg
 */
UT_CASE_DECLARATION(_queue_push__queue_push_varg)
void test__queue_push__queue_push_varg__null_queue_adaptor(void** state);
void test__queue_push__queue_push_varg__non_inited_queue_adaptor(void** state);
void test__queue_push__queue_push_varg__empty(void** state);
void test__queue_push__queue_push_varg__non_empty(void** state);
void test__queue_push__queue_push_varg__non_empty_multiple(void** state);

#define UT_CSTL_QUEUE_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_queue_private, test__create_queue__null_typename),\
    UT_CASE(test__create_queue__unregisted_type),\
    UT_CASE(test__create_queue__c_builtin_type),\
    UT_CASE(test__create_queue__libcstl_builtin_type),\
    UT_CASE(test__create_queue__user_defined_type),\
    UT_CASE(test__create_queue__user_defined_type_dup),\
    UT_CASE_BEGIN(_create_queue_auxiliary, test__create_queue_auxiliary__null_queue_adaptor),\
    UT_CASE(test__create_queue_auxiliary__null_typename),\
    UT_CASE(test__create_queue_auxiliary__unregisted_type),\
    UT_CASE(test__create_queue_auxiliary__c_builtin),\
    UT_CASE(test__create_queue_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_queue_auxiliary__user_defined),\
    UT_CASE(test__create_queue_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_queue_destroy_auxiliary, test__queue_destroy_auxiliary__null_queue_adaptor),\
    UT_CASE(test__queue_destroy_auxiliary__non_created_queue_adaptor),\
    UT_CASE(test__queue_destroy_auxiliary__non_inited),\
    UT_CASE(test__queue_destroy_auxiliary__empty),\
    UT_CASE(test__queue_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_queue_push__queue_push_varg,\
        test__queue_push__queue_push_varg__null_queue_adaptor),\
    UT_CASE(test__queue_push__queue_push_varg__non_inited_queue_adaptor),\
    UT_CASE(test__queue_push__queue_push_varg__empty),\
    UT_CASE(test__queue_push__queue_push_varg__non_empty),\
    UT_CASE(test__queue_push__queue_push_varg__non_empty_multiple)

#endif /* _UT_CSTL_QUEUE_PRIVATE_H_ */

