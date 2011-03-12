#ifndef _UT_CSTL_STRING_H_
#define _UT_CSTL_STRING_H_

UT_SUIT_DECLARATION(cstl_string)

/*
 * test create_string
 */
UT_CASE_DECLARATION(create_string)
void test_create_string__successfully(void** state);
/*
 * test string_init
 */
UT_CASE_DECLARATION(string_init)
void test_string_init__null_string_container(void** state);
void test_string_init__non_created(void** state);
void test_string_init__successfully(void** state);
/*
 * test string_init_char
 */
UT_CASE_DECLARATION(string_init_char)
void test_string_init_char__null(void** state);
void test_string_init_char__non_created(void** state);
void test_string_init_char__empty(void** state);
void test_string_init_char__non_empty(void** state);
/*
 * test string_init_cstr
 */
UT_CASE_DECLARATION(string_init_cstr)
void test_string_init_cstr__null(void** state);
void test_string_init_cstr__non_created(void** state);
void test_string_init_cstr__null_cstr(void** state);
void test_string_init_cstr__empty(void** state);
void test_string_init_cstr__non_empty(void** state);
void test_string_init_cstr__cut_off_empty(void** state);
void test_string_init_cstr__cut_off_non_empty(void** state);

#define UT_CSTL_STRING_CASE\
    UT_SUIT_BEGIN(cstl_string, test_create_string__successfully),\
    UT_CASE_BEGIN(string_init, test_string_init__null_string_container),\
    UT_CASE(test_string_init__non_created),\
    UT_CASE(test_string_init__successfully),\
    UT_CASE_BEGIN(string_init, test_string_init_char__null),\
    UT_CASE(test_string_init_char__non_created),\
    UT_CASE(test_string_init_char__empty),\
    UT_CASE(test_string_init_char__non_empty),\
    UT_CASE_BEGIN(string_init_cstr, test_string_init_cstr__null),\
    UT_CASE(test_string_init_cstr__non_created),\
    UT_CASE(test_string_init_cstr__null_cstr),\
    UT_CASE(test_string_init_cstr__empty),\
    UT_CASE(test_string_init_cstr__non_empty),\
    UT_CASE(test_string_init_cstr__cut_off_empty),\
    UT_CASE(test_string_init_cstr__cut_off_non_empty),\

#endif /* _UT_CSTL_STRING_H_ */

