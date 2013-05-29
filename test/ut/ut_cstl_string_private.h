#ifndef _UT_CSTL_STRING_PRIVATE_H_
#define _UT_CSTL_STRING_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_string_private)

/*
 * test _create_string_auxiliary
 */
UT_CASE_DECLARATION(_create_string_auxiliary)
void test__create_string_auxiliary__null_string_container(void** state);
void test__create_string_auxiliary__successfully(void** state);
/*
 * test _string_destroy_auxiliary
 */
UT_CASE_DECLARATION(_string_destroy_auxiliary)
void test__string_destroy_auxiliary__null_string_container(void** state);
void test__string_destroy_auxiliary__invalid_string_container(void** state);
void test__string_destroy_auxiliary__successfully_non_init_container(void** state);
void test__string_destroy_auxiliary__successfully_empty_container(void** state);
void test__string_destroy_auxiliary__successfully(void** state);

#define UT_CSTL_STRING_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_string_private, test__create_string_auxiliary__null_string_container),\
    UT_CASE(test__create_string_auxiliary__successfully),\
    UT_CASE_BEGIN(_string_destroy_auxiliary, test__string_destroy_auxiliary__null_string_container),\
    UT_CASE(test__string_destroy_auxiliary__invalid_string_container),\
    UT_CASE(test__string_destroy_auxiliary__successfully_non_init_container),\
    UT_CASE(test__string_destroy_auxiliary__successfully_empty_container),\
    UT_CASE(test__string_destroy_auxiliary__successfully)

#endif /* _UT_CSTL_STRING_PRIVATE_H_ */

