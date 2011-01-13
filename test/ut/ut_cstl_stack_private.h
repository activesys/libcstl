#ifndef _UT_CSTL_STACK_PRIVATE_H_
#define _UT_CSTL_STACK_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_stack_private)

/*
 * test _create_stack
 */
UT_CASE_DECLARATION(_create_stack)
void test__create_stack__null_typename(void** state);
void test__create_stack__unregisted_type(void** state);
void test__create_stack__c_builtin_type(void** state);
void test__create_stack__libcstl_builtin_type(void** state);
void test__create_stack__user_defined_type(void** state);
void test__create_stack__user_defined_type_dup(void** state);
/*
 * test _create_stack_auxiliary
 */
UT_CASE_DECLARATION(_create_stack_auxiliary)
void test__create_stack_auxiliary__null_stack_adaptor(void** state);
void test__create_stack_auxiliary__null_typename(void** state);
void test__create_stack_auxiliary__unregisted_type(void** state);
void test__create_stack_auxiliary__c_builtin(void** state);
void test__create_stack_auxiliary__libcstl_builtin(void** state);
void test__create_stack_auxiliary__user_defined(void** state);
void test__create_stack_auxiliary__user_defined_dup(void** state);
/*
 * test _stack_destroy_auxiliary
 */
UT_CASE_DECLARATION(_stack_destroy_auxiliary)
void test__stack_destroy_auxiliary__null_stack_adaptor(void** state);
void test__stack_destroy_auxiliary__non_created_stack_adaptor(void** state);
void test__stack_destroy_auxiliary__non_inited(void** state);
void test__stack_destroy_auxiliary__empty(void** state);
void test__stack_destroy_auxiliary__non_empty(void** state);
/*
 * test _stack_push and _stack_push_varg
 */
UT_CASE_DECLARATION(_stack_push__stack_push_varg)
void test__stack_push__stack_push_varg__null_stack_adaptor(void** state);
void test__stack_push__stack_push_varg__non_inited_stack_adaptor(void** state);
void test__stack_push__stack_push_varg__empty(void** state);
void test__stack_push__stack_push_varg__non_empty(void** state);
void test__stack_push__stack_push_varg__non_empty_multiple(void** state);

#define UT_CSTL_STACK_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_stack_private, test__create_stack__null_typename),\
    UT_CASE(test__create_stack__unregisted_type),\
    UT_CASE(test__create_stack__c_builtin_type),\
    UT_CASE(test__create_stack__libcstl_builtin_type),\
    UT_CASE(test__create_stack__user_defined_type),\
    UT_CASE(test__create_stack__user_defined_type_dup),\
    UT_CASE_BEGIN(_create_stack_auxiliary, test__create_stack_auxiliary__null_stack_adaptor),\
    UT_CASE(test__create_stack_auxiliary__null_typename),\
    UT_CASE(test__create_stack_auxiliary__unregisted_type),\
    UT_CASE(test__create_stack_auxiliary__c_builtin),\
    UT_CASE(test__create_stack_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_stack_auxiliary__user_defined),\
    UT_CASE(test__create_stack_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_stack_destroy_auxiliary, test__stack_destroy_auxiliary__null_stack_adaptor),\
    UT_CASE(test__stack_destroy_auxiliary__non_created_stack_adaptor),\
    UT_CASE(test__stack_destroy_auxiliary__non_inited),\
    UT_CASE(test__stack_destroy_auxiliary__empty),\
    UT_CASE(test__stack_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_stack_push__stack_push_varg,\
        test__stack_push__stack_push_varg__null_stack_adaptor),\
    UT_CASE(test__stack_push__stack_push_varg__non_inited_stack_adaptor),\
    UT_CASE(test__stack_push__stack_push_varg__empty),\
    UT_CASE(test__stack_push__stack_push_varg__non_empty),\
    UT_CASE(test__stack_push__stack_push_varg__non_empty_multiple)

#endif /* _UT_CSTL_STACK_PRIVATE_H_ */

