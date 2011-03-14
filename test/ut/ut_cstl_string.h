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
void test_string_init_cstr__truncate_empty(void** state);
void test_string_init_cstr__truncate_non_empty(void** state);
/*
 * test string_init_subcstr
 */
UT_CASE_DECLARATION(string_init_subcstr)
void test_string_init_subcstr__null_container(void** state);
void test_string_init_subcstr__non_created_container(void** state);
void test_string_init_subcstr__null_cstr(void** state);
void test_string_init_subcstr__cstr_empty(void** state);
void test_string_init_subcstr__length_empty(void** state);
void test_string_init_subcstr__non_empty(void** state);
void test_string_init_subcstr__all(void** state);
void test_string_init_subcstr__truncate_empty(void** state);
void test_string_init_subcstr__truncate_non_empty(void** state);
/*
 * test string_init_copy
 */
UT_CASE_DECLARATION(string_init_copy)
void test_string_init_copy__null_dest(void** state);
void test_string_init_copy__null_src(void** state);
void test_string_init_copy__non_create_dest(void** state);
void test_string_init_copy__non_inited_src(void** state);
void test_string_init_copy__empty(void** state);
void test_string_init_copy__non_empty(void** state);
/*
 * test string_init_copy_substring
 */
UT_CASE_DECLARATION(string_init_copy_substring)
void test_string_init_copy_substring__null_dest(void** state);
void test_string_init_copy_substring__null_src(void** state);
void test_string_init_copy_substring__non_create_dest(void** state);
void test_string_init_copy_substring__non_inited_src(void** state);
void test_string_init_copy_substring__src_non_empty_begin_empty(void** state);
void test_string_init_copy_substring__src_non_empty_begin_non_empty(void** state);
void test_string_init_copy_substring__src_non_empty_begin_length(void** state);
void test_string_init_copy_substring__src_non_empty_begin_npos(void** state);
void test_string_init_copy_substring__src_non_empty_middle_empty(void** state);
void test_string_init_copy_substring__src_non_empty_middle_non_empty(void** state);
void test_string_init_copy_substring__src_non_empty_middle_length(void** state);
void test_string_init_copy_substring__src_non_empty_middle_npos(void** state);
void test_string_init_copy_substring__src_non_empty_end(void** state);
void test_string_init_copy_substring__src_non_empty_npos(void** state);
/*
 * test string_init_copy_range
 */
UT_CASE_DECLARATION(string_init_copy_range)
void test_string_init_copy_range__null_dest(void** state);
void test_string_init_copy_range__invalid_begin_iterator(void** state);
void test_string_init_copy_range__invalid_end_iterator(void** state);
void test_string_init_copy_range__invalid_range(void** state);
void test_string_init_copy_range__empty_range(void** state);
void test_string_init_copy_range__not_empty_range(void** state);
/*
 * test string_destroy
 */
UT_CASE_DECLARATION(string_destroy)
void test_string_destroy__null_string_container(void** state);
void test_string_destroy__non_created(void** state);
void test_string_destroy__created_non_inited(void** state);
void test_string_destroy__inited_empty(void** state);
void test_string_destroy__inited_non_empty(void** state);
/*
 * test string_c_str
 */
UT_CASE_DECLARATION(string_c_str)
void test_string_c_str__null_container(void** state);
void test_string_c_str__non_inited_container(void** state);
void test_string_c_str__empty(void** state);
void test_string_c_str__non_empty(void** state);
/*
 * test string_data
 */
UT_CASE_DECLARATION(string_data)
void test_string_data__null_container(void** state);
void test_string_data__non_inited_container(void** state);
void test_string_data__empty(void** state);
void test_string_data__non_empty(void** state);
/*
 * test string_copy
 */
UT_CASE_DECLARATION(string_copy)
void test_string_copy__null_container(void** state);
void test_string_copy__non_inited_container(void** state);
void test_string_copy__null_buffer(void** state);
void test_string_copy__invalid_position(void** state);
void test_string_copy__begin_empty(void** state);
void test_string_copy__begin_non_empty(void** state);
void test_string_copy__begin_length(void** state);
void test_string_copy__begin_npos(void** state);
void test_string_copy__middle_empty(void** state);
void test_string_copy__middle_non_empty(void** state);
void test_string_copy__middle_length(void** state);
void test_string_copy__middle_npos(void** state);
void test_string_copy__end(void** state);
void test_string_copy__npos(void** state);
/*
 * test string_size
 */
UT_CASE_DECLARATION(string_size)
void test_string_size__null_string_container(void** state);
void test_string_size__non_inited(void** state);
void test_string_size__successfully_empty(void** state);
void test_string_size__successfully_non_empty(void** state);
/*
 * test string_length
 */
UT_CASE_DECLARATION(string_length)
void test_string_length__null_string_container(void** state);
void test_string_length__non_inited(void** state);
void test_string_length__successfully_empty(void** state);
void test_string_length__successfully_non_empty(void** state);
/*
 * test string_empty
 */
UT_CASE_DECLARATION(string_empty)
void test_string_empty__null_string_container(void** state);
void test_string_empty__non_inited(void** state);
void test_string_empty__successfully_empty(void** state);
void test_string_empty__successfully_non_empty(void** state);
/*
 * test string_max_size
 */
UT_CASE_DECLARATION(string_max_size)
void test_string_max_size__null_string_container(void** state);
void test_string_max_size__non_inited(void** state);
void test_string_max_size__successfully(void** state);
/*
 * test string_capacity
 */
UT_CASE_DECLARATION(string_capacity)
void test_string_capacity__null_string_container(void** state);
void test_string_capacity__non_inited(void** state);
void test_string_capacity__successfully_empty(void** state);
void test_string_capacity__successfully_little(void** state);
void test_string_capacity__successfully_huge(void** state);

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
    UT_CASE(test_string_init_cstr__truncate_empty),\
    UT_CASE(test_string_init_cstr__truncate_non_empty),\
    UT_CASE_BEGIN(string_init_subcstr, test_string_init_subcstr__null_container),\
    UT_CASE(test_string_init_subcstr__non_created_container),\
    UT_CASE(test_string_init_subcstr__null_cstr),\
    UT_CASE(test_string_init_subcstr__cstr_empty),\
    UT_CASE(test_string_init_subcstr__length_empty),\
    UT_CASE(test_string_init_subcstr__non_empty),\
    UT_CASE(test_string_init_subcstr__all),\
    UT_CASE(test_string_init_subcstr__truncate_empty),\
    UT_CASE(test_string_init_subcstr__truncate_non_empty),\
    UT_CASE_BEGIN(string_init_copy, test_string_init_copy__null_dest),\
    UT_CASE(test_string_init_copy__null_src),\
    UT_CASE(test_string_init_copy__non_create_dest),\
    UT_CASE(test_string_init_copy__non_inited_src),\
    UT_CASE(test_string_init_copy__empty),\
    UT_CASE(test_string_init_copy__non_empty),\
    UT_CASE_BEGIN(string_init_copy_substring, test_string_init_copy_substring__null_dest),\
    UT_CASE(test_string_init_copy_substring__null_src),\
    UT_CASE(test_string_init_copy_substring__non_create_dest),\
    UT_CASE(test_string_init_copy_substring__non_inited_src),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_non_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_length),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_begin_npos),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_non_empty),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_length),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_middle_npos),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_end),\
    UT_CASE(test_string_init_copy_substring__src_non_empty_npos),\
    UT_CASE_BEGIN(string_init_copy_range, test_string_init_copy_range__null_dest),\
    UT_CASE(test_string_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_string_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_string_init_copy_range__invalid_range),\
    UT_CASE(test_string_init_copy_range__empty_range),\
    UT_CASE(test_string_init_copy_range__not_empty_range),\
    UT_CASE_BEGIN(string_destroy, test_string_destroy__null_string_container),\
    UT_CASE(test_string_destroy__non_created),\
    UT_CASE(test_string_destroy__created_non_inited),\
    UT_CASE(test_string_destroy__inited_empty),\
    UT_CASE(test_string_destroy__inited_non_empty),\
    UT_CASE_BEGIN(string_c_str, test_string_c_str__null_container),\
    UT_CASE(test_string_c_str__non_inited_container),\
    UT_CASE(test_string_c_str__empty),\
    UT_CASE(test_string_c_str__non_empty),\
    UT_CASE_BEGIN(string_data, test_string_data__null_container),\
    UT_CASE(test_string_data__non_inited_container),\
    UT_CASE(test_string_data__empty),\
    UT_CASE(test_string_data__non_empty),\
    UT_CASE_BEGIN(string_copy, test_string_copy__null_container),\
    UT_CASE(test_string_copy__non_inited_container),\
    UT_CASE(test_string_copy__null_buffer),\
    UT_CASE(test_string_copy__invalid_position),\
    UT_CASE(test_string_copy__begin_empty),\
    UT_CASE(test_string_copy__begin_non_empty),\
    UT_CASE(test_string_copy__begin_length),\
    UT_CASE(test_string_copy__begin_npos),\
    UT_CASE(test_string_copy__middle_empty),\
    UT_CASE(test_string_copy__middle_non_empty),\
    UT_CASE(test_string_copy__middle_length),\
    UT_CASE(test_string_copy__middle_npos),\
    UT_CASE(test_string_copy__end),\
    UT_CASE(test_string_copy__npos),\
    UT_CASE_BEGIN(string_size, test_string_size__null_string_container),\
    UT_CASE(test_string_size__non_inited),\
    UT_CASE(test_string_size__successfully_empty),\
    UT_CASE(test_string_size__successfully_non_empty),\
    UT_CASE_BEGIN(string_length, test_string_length__null_string_container),\
    UT_CASE(test_string_length__non_inited),\
    UT_CASE(test_string_length__successfully_empty),\
    UT_CASE(test_string_length__successfully_non_empty),\
    UT_CASE_BEGIN(string_empty, test_string_empty__null_string_container),\
    UT_CASE(test_string_empty__non_inited),\
    UT_CASE(test_string_empty__successfully_empty),\
    UT_CASE(test_string_empty__successfully_non_empty),\
    UT_CASE_BEGIN(string_empty, test_string_max_size__null_string_container),\
    UT_CASE(test_string_max_size__non_inited),\
    UT_CASE(test_string_max_size__successfully),\
    UT_CASE_BEGIN(string_capacity, test_string_capacity__null_string_container),\
    UT_CASE(test_string_capacity__non_inited),\
    UT_CASE(test_string_capacity__successfully_empty),\
    UT_CASE(test_string_capacity__successfully_little),\
    UT_CASE(test_string_capacity__successfully_huge),\

#endif /* _UT_CSTL_STRING_H_ */

