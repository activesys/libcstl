#ifndef _UT_CSTL_VECTOR_H_
#define _UT_CSTL_VECTOR_H_

UT_SUIT_DECLARATION(cstl_vector)

/*
 * test vector_init
 */
UT_CASE_DECLARATION(vector_init)
void test_vector_init__null_vector_container(void** state);
void test_vector_init__non_created(void** state);
void test_vector_init__successfully_c_builtin(void** state);
void test_vector_init__successfully_cstl_builtin(void** state);
void test_vector_init__successfully_cstr(void** state);
void test_vector_init__successfully_user_defined(void** state);
/*
 * test vector_init_n
 */
UT_CASE_DECLARATION(vector_init_n)
void test_vector_init_n__null_vector_container(void** state);
void test_vector_init_n__non_created(void** state);
void test_vector_init_n__successfully_0(void** state);
void test_vector_init_n__successfully_c_builtin(void** state);
void test_vector_init_n__successfully_cstr(void** state);
void test_vector_init_n__successfully_cstl_builtin(void** state);
void test_vector_init_n__successfully_user_defined(void** state);

#define UT_CSTL_VECTOR_CASE\
    UT_SUIT_BEGIN(cstl_vector, test_vector_init__null_vector_container),\
    UT_CASE(test_vector_init__non_created),\
    UT_CASE(test_vector_init__successfully_c_builtin),\
    UT_CASE(test_vector_init__successfully_cstl_builtin),\
    UT_CASE(test_vector_init__successfully_cstr),\
    UT_CASE(test_vector_init__successfully_user_defined),\
    UT_CASE_BEGIN(vector_init_n, test_vector_init_n__null_vector_container),\
    UT_CASE(test_vector_init_n__non_created),\
    UT_CASE(test_vector_init_n__successfully_0),\
    UT_CASE(test_vector_init_n__successfully_c_builtin),\
    UT_CASE(test_vector_init_n__successfully_cstr),\
    UT_CASE(test_vector_init_n__successfully_cstl_builtin),\
    UT_CASE(test_vector_init_n__successfully_user_defined)

#endif /* _UT_CSTL_VECTOR_H_ */

