#ifndef _UT_CSTL_SET_H_
#define _UT_CSTL_SET_H_

UT_SUIT_DECLARATION(cstl_set)
/*
 * test set_init
 */
UT_CASE_DECLARATION(set_init)
void test_set_init__null_set(void** state);
void test_set_init__non_created(void** state);
void test_set_init__null_compare(void** state);
/*
 * test set_init_ex
 */
UT_CASE_DECLARATION(set_init_ex)
void test_set_init_ex__null_set(void** state);
void test_set_init_ex__non_created(void** state);
void test_set_init_ex__null_compare(void** state);
void test_set_init_ex__non_null_compare(void** state);

#define UT_CSTL_SET_CASE\
    UT_SUIT_BEGIN(cstl_set, test_set_init__null_set),\
    UT_CASE(test_set_init__non_created),\
    UT_CASE(test_set_init__null_compare),\
    UT_CASE_BEGIN(set_init_ex,  test_set_init_ex__null_set),\
    UT_CASE(test_set_init_ex__non_created),\
    UT_CASE(test_set_init_ex__null_compare),\
    UT_CASE(test_set_init_ex__non_null_compare),\

#endif /* _UT_CSTL_SET_H_ */

