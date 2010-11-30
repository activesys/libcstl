#ifndef _UT_CSTL_VECTOR_PRIVATE_H_
#define _UT_CSTL_VECTOR_PRIVATE_H_

/*
 * test _create_vector
 */
void test__create_vector__null_typename(void** state);
void test__create_vector__unregisted_type(void** state);
void test__create_vector__c_builtin_type(void** state);
void test__create_vector__libcstl_builtin_type(void** state);
void test__create_vector__registed_type(void** state);

#define UT_CSTL_VECTOR_PRIVATE_CASE \
    unit_test(test__create_vector__null_typename),\
    unit_test(test__create_vector__unregisted_type),\
    unit_test(test__create_vector__c_builtin_type),\
    unit_test(test__create_vector__libcstl_builtin_type),\
    unit_test(test__create_vector__registed_type)

#endif /* _UT_CSTL_VECTOR_PRIVATE_H_ */

