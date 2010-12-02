#ifndef _UT_CSTL_VECTOR_PRIVATE_H_
#define _UT_CSTL_VECTOR_PRIVATE_H_

UT_CASE_DECLARATION(cstl_vector_private)

/*
 * test _create_vector
 */
UT_ITEM_DECLARATION(_create_vector)
void test__create_vector__null_typename(void** state);
void test__create_vector__unregisted_type(void** state);
void test__create_vector__c_builtin_type(void** state);
void test__create_vector__libcstl_builtin_type(void** state);
void test__create_vector__registed_type(void** state);

#define UT_CSTL_VECTOR_PRIVATE_CASE \
    UT_CASE(cstl_vector_private),\
    UT_ITEM(_create_vector),\
    unit_test(test__create_vector__null_typename),\
    unit_test(test__create_vector__unregisted_type),\
    unit_test(test__create_vector__c_builtin_type),\
    unit_test(test__create_vector__libcstl_builtin_type),\
    unit_test(test__create_vector__registed_type)

#endif /* _UT_CSTL_VECTOR_PRIVATE_H_ */

