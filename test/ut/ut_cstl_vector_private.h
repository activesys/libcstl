#ifndef _UT_CSTL_VECTOR_PRIVATE_H_
#define _UT_CSTL_VECTOR_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_vector_private)

/*
 * test _create_vector
 */
UT_CASE_DECLARATION(_create_vector)
void test__create_vector__null_typename(void** state);
void test__create_vector__unregisted_type(void** state);
void test__create_vector__c_builtin_type(void** state);
void test__create_vector__libcstl_builtin_type(void** state);
void test__create_vector__registed_type(void** state);

#define UT_CSTL_VECTOR_PRIVATE_CASE \
    UT_SUIT_BEGIN(cstl_vector_private, test__create_vector__null_typename),\
    UT_CASE(test__create_vector__unregisted_type),\
    UT_CASE(test__create_vector__c_builtin_type),\
    UT_CASE(test__create_vector__libcstl_builtin_type),\
    UT_CASE(test__create_vector__registed_type)

#endif /* _UT_CSTL_VECTOR_PRIVATE_H_ */

