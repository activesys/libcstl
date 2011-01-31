#ifndef _UT_CSTL_BASIC_STRING_H_
#define _UT_CSTL_BASIC_STRING_H_

UT_SUIT_DECLARATION(cstl_basic_string)

/*
 * test basic_string_init
 */
UT_CASE_DECLARATION(basic_string_init)
void test_basic_string_init__null_basic_string_container(void** state);
void test_basic_string_init__non_created(void** state);
void test_basic_string_init__successfully_c_builtin(void** state);
void test_basic_string_init__successfully_cstl_builtin(void** state);
void test_basic_string_init__successfully_cstr(void** state);
void test_basic_string_init__successfully_user_defined(void** state);
/*
 * test basic_string_init_cstr
 */
UT_CASE_DECLARATION(basic_string_init_cstr)
void test_basic_string_init_cstr__null_container(void** state);
void test_basic_string_init_cstr__non_created_container(void** state);
void test_basic_string_init_cstr__null_valuestring(void** state);
void test_basic_string_init_cstr__c_builtin_init_empty(void** state);
void test_basic_string_init_cstr__c_builtin_init_non_empty(void** state);
void test_basic_string_init_cstr__char_init_empty(void** state);
void test_basic_string_init_cstr__char_init_non_empty(void** state);
void test_basic_string_init_cstr__cstr_init_empty(void** state);
void test_basic_string_init_cstr__cstr_init_non_empty(void** state);
void test_basic_string_init_cstr__libcstl_builtin_empty(void** state);
void test_basic_string_init_cstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_init_cstr__user_define_empty(void** state);
void test_basic_string_init_cstr__user_define_non_empty(void** state);
/*
 * test basic_string_init_subcstr
 */
UT_CASE_DECLARATION(basic_string_init_subcstr)
void test_basic_string_init_subcstr__null_container(void** state);
void test_basic_string_init_subcstr__non_created_container(void** state);
void test_basic_string_init_subcstr__null_valuestring(void** state);
void test_basic_string_init_subcstr__c_builtin_init_empty(void** state);
void test_basic_string_init_subcstr__c_builtin_init_non_empty(void** state);
void test_basic_string_init_subcstr__c_builtin_init_total(void** state);
void test_basic_string_init_subcstr__char_init_empty(void** state);
void test_basic_string_init_subcstr__char_init_non_empty(void** state);
void test_basic_string_init_subcstr__char_init_total(void** state);
void test_basic_string_init_subcstr__cstr_init_empty(void** state);
void test_basic_string_init_subcstr__cstr_init_non_empty(void** state);
void test_basic_string_init_subcstr__cstr_init_total(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_empty(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_non_empty(void** state);
void test_basic_string_init_subcstr__libcstl_builtin_total(void** state);
void test_basic_string_init_subcstr__user_define_empty(void** state);
void test_basic_string_init_subcstr__user_define_non_empty(void** state);
void test_basic_string_init_subcstr__user_define_total(void** state);
/*
 * test basic_string_init_copy
 */
UT_CASE_DECLARATION(basic_string_init_copy)
void test_basic_string_init_copy__null_dest(void** state);
void test_basic_string_init_copy__null_src(void** state);
void test_basic_string_init_copy__non_create_dest(void** state);
void test_basic_string_init_copy__non_inited_src(void** state);
void test_basic_string_init_copy__not_same_type(void** state);
void test_basic_string_init_copy__successfully_c_builtin_empty(void** state);
void test_basic_string_init_copy__successfully_c_builtin_little(void** state);
void test_basic_string_init_copy__successfully_c_builtin_huge(void** state);
void test_basic_string_init_copy__successfully_cstr_empty(void** state);
void test_basic_string_init_copy__successfully_cstr_little(void** state);
void test_basic_string_init_copy__successfully_cstr_huge(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_empty(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_little(void** state);
void test_basic_string_init_copy__successfully_cstl_builtin_huge(void** state);
void test_basic_string_init_copy__successfully_user_define_empty(void** state);
void test_basic_string_init_copy__successfully_user_define_little(void** state);
void test_basic_string_init_copy__successfully_user_define_huge(void** state);
/*
 * test basic_string_init_copy_substring
 */
UT_CASE_DECLARATION(basic_string_init_copy_substring)
void test_basic_string_init_copy_substring__null_dest(void** state);
void test_basic_string_init_copy_substring__null_src(void** state);
void test_basic_string_init_copy_substring__non_create_dest(void** state);
void test_basic_string_init_copy_substring__non_inited_src(void** state);
void test_basic_string_init_copy_substring__not_same_type(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_src_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_length(void** state);
void test_basic_string_init_copy_substring__successfully_cstl_builtin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_length(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_non_empty(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_length(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_npos(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_end(void** state);
void test_basic_string_init_copy_substring__successfully_user_define_non_empty_npos(void** state);
/*
 * test basic_string_init_copy_range
 */
UT_CASE_DECLARATION(basic_string_init_copy_range)
void test_basic_string_init_copy_range__null_dest(void** state);
void test_basic_string_init_copy_range__invalid_begin_iterator(void** state);
void test_basic_string_init_copy_range__invalid_end_iterator(void** state);
void test_basic_string_init_copy_range__invalid_range(void** state);
void test_basic_string_init_copy_range__not_same_type(void** state);
void test_basic_string_init_copy_range__successfully_empty_range(void** state);
void test_basic_string_init_copy_range__successfully_c_builtin(void** state);
void test_basic_string_init_copy_range__successfully_cstr(void** state);
void test_basic_string_init_copy_range__successfully_cstl_builtin(void** state);
void test_basic_string_init_copy_range__successfully_user_define(void** state);
/*
 * test basic_string_destroy
 */
UT_CASE_DECLARATION(basic_string_destroy)
void test_basic_string_destroy__null_basic_string_container(void** state);
void test_basic_string_destroy__non_created(void** state);
void test_basic_string_destroy__created_non_inited(void** state);
void test_basic_string_destroy__inited_empty(void** state);
void test_basic_string_destroy__inited_non_empty(void** state);
/*
 * test basic_string_c_str
 */
UT_CASE_DECLARATION(basic_string_c_str)
void test_basic_string_c_str__null_container(void** state);
void test_basic_string_c_str__non_inited_container(void** state);
void test_basic_string_c_str__empty(void** state);
void test_basic_string_c_str__non_empty(void** state);
/*
 * test basic_string_data
 */
UT_CASE_DECLARATION(basic_string_data)
void test_basic_string_data__null_container(void** state);
void test_basic_string_data__non_inited_container(void** state);
void test_basic_string_data__empty(void** state);
void test_basic_string_data__non_empty(void** state);
/*
 * test basic_string_copy
 */
UT_CASE_DECLARATION(basic_string_copy)
void test_basic_string_copy__null_container(void** state);
void test_basic_string_copy__non_inited_container(void** state);
void test_basic_string_copy__null_buffer(void** state);
void test_basic_string_copy__invalid_position(void** state);
void test_basic_string_copy__begin_empty(void** state);
void test_basic_string_copy__begin_non_empty(void** state);
void test_basic_string_copy__begin_length(void** state);
void test_basic_string_copy__begin_npos(void** state);
void test_basic_string_copy__middle_empty(void** state);
void test_basic_string_copy__middle_non_empty(void** state);
void test_basic_string_copy__middle_length(void** state);
void test_basic_string_copy__middle_npos(void** state);
void test_basic_string_copy__end(void** state);
void test_basic_string_copy__npos(void** state);
/*
 * test basic_string_size
 */
UT_CASE_DECLARATION(basic_string_size)
void test_basic_string_size__null_basic_string_container(void** state);
void test_basic_string_size__non_inited(void** state);
void test_basic_string_size__successfully_empty(void** state);
void test_basic_string_size__successfully_non_empty(void** state);
/*
 * test basic_string_length
 */
UT_CASE_DECLARATION(basic_string_length)
void test_basic_string_length__null_basic_string_container(void** state);
void test_basic_string_length__non_inited(void** state);
void test_basic_string_length__successfully_empty(void** state);
void test_basic_string_length__successfully_non_empty(void** state);
/*
 * test basic_string_empty
 */
UT_CASE_DECLARATION(basic_string_empty)
void test_basic_string_empty__null_basic_string_container(void** state);
void test_basic_string_empty__non_inited(void** state);
void test_basic_string_empty__successfully_empty(void** state);
void test_basic_string_empty__successfully_non_empty(void** state);
/*
 * test basic_string_max_size
 */
UT_CASE_DECLARATION(basic_string_max_size)
void test_basic_string_max_size__null_basic_string_container(void** state);
void test_basic_string_max_size__non_inited(void** state);
void test_basic_string_max_size__successfully(void** state);
/*
 * test basic_string_capacity
 */
UT_CASE_DECLARATION(basic_string_capacity)
void test_basic_string_capacity__null_basic_string_container(void** state);
void test_basic_string_capacity__non_inited(void** state);
void test_basic_string_capacity__successfully_empty(void** state);
void test_basic_string_capacity__successfully_little(void** state);
void test_basic_string_capacity__successfully_huge(void** state);
/*
 * test basic_string_at
 */
UT_CASE_DECLARATION(basic_string_at)
void test_basic_string_at__null_basic_string_container(void** state);
void test_basic_string_at__non_inited_basic_string_container(void** state);
void test_basic_string_at__invalid_subscript_empty(void** state);
void test_basic_string_at__invalid_subscript_end(void** state);
void test_basic_string_at__invalid_subscript(void** state);
void test_basic_string_at__successfully(void** state);
void test_basic_string_at__successfully_cstr(void** state);

#define UT_CSTL_BASIC_STRING_CASE\
    UT_SUIT_BEGIN(cstl_basic_string, test_basic_string_init__null_basic_string_container),\
    UT_CASE(test_basic_string_init__non_created),\
    UT_CASE(test_basic_string_init__successfully_c_builtin),\
    UT_CASE(test_basic_string_init__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_init__successfully_cstr),\
    UT_CASE(test_basic_string_init__successfully_user_defined),\
    UT_CASE_BEGIN(basic_string_init_cstr, test_basic_string_init_cstr__null_container),\
    UT_CASE(test_basic_string_init_cstr__non_created_container),\
    UT_CASE(test_basic_string_init_cstr__null_valuestring),\
    UT_CASE(test_basic_string_init_cstr__c_builtin_init_empty),\
    UT_CASE(test_basic_string_init_cstr__c_builtin_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__char_init_empty),\
    UT_CASE(test_basic_string_init_cstr__char_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__cstr_init_empty),\
    UT_CASE(test_basic_string_init_cstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_init_cstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_init_cstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_init_cstr__user_define_empty),\
    UT_CASE(test_basic_string_init_cstr__user_define_non_empty),\
    UT_CASE_BEGIN(basic_string_init_subcstr, test_basic_string_init_subcstr__null_container),\
    UT_CASE(test_basic_string_init_subcstr__non_created_container),\
    UT_CASE(test_basic_string_init_subcstr__null_valuestring),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__c_builtin_init_total),\
    UT_CASE(test_basic_string_init_subcstr__char_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__char_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__char_init_total),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_empty),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__cstr_init_total),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_empty),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__libcstl_builtin_total),\
    UT_CASE(test_basic_string_init_subcstr__user_define_empty),\
    UT_CASE(test_basic_string_init_subcstr__user_define_non_empty),\
    UT_CASE(test_basic_string_init_subcstr__user_define_total),\
    UT_CASE_BEGIN(basic_string_init_copy, test_basic_string_init_copy__null_dest),\
    UT_CASE(test_basic_string_init_copy__null_src),\
    UT_CASE(test_basic_string_init_copy__non_create_dest),\
    UT_CASE(test_basic_string_init_copy__non_inited_src),\
    UT_CASE(test_basic_string_init_copy__not_same_type),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_little),\
    UT_CASE(test_basic_string_init_copy__successfully_c_builtin_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_little),\
    UT_CASE(test_basic_string_init_copy__successfully_cstr_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_little),\
    UT_CASE(test_basic_string_init_copy__successfully_cstl_builtin_huge),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_empty),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_little),\
    UT_CASE(test_basic_string_init_copy__successfully_user_define_huge),\
    UT_CASE_BEGIN(basic_string_init_copy_substring,\
        test_basic_string_init_copy_substring__null_dest),\
    UT_CASE(test_basic_string_init_copy_substring__null_src),\
    UT_CASE(test_basic_string_init_copy_substring__non_create_dest),\
    UT_CASE(test_basic_string_init_copy_substring__non_inited_src),\
    UT_CASE(test_basic_string_init_copy_substring__not_same_type),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_c_builtin_src_non_empty_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstr_src_non_empty_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_src_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_cstl_builtin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_begin_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_non_empty),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_length),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_middle_npos),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_end),\
    UT_CASE(test_basic_string_init_copy_substring__successfully_user_define_non_empty_npos),\
    UT_CASE_BEGIN(basic_string_init_copy_range, test_basic_string_init_copy_range__null_dest),\
    UT_CASE(test_basic_string_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_basic_string_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_basic_string_init_copy_range__invalid_range),\
    UT_CASE(test_basic_string_init_copy_range__not_same_type),\
    UT_CASE(test_basic_string_init_copy_range__successfully_empty_range),\
    UT_CASE(test_basic_string_init_copy_range__successfully_c_builtin),\
    UT_CASE(test_basic_string_init_copy_range__successfully_cstr),\
    UT_CASE(test_basic_string_init_copy_range__successfully_cstl_builtin),\
    UT_CASE(test_basic_string_init_copy_range__successfully_user_define),\
    UT_CASE_BEGIN(basic_string_destroy, test_basic_string_destroy__null_basic_string_container),\
    UT_CASE(test_basic_string_destroy__non_created),\
    UT_CASE(test_basic_string_destroy__created_non_inited),\
    UT_CASE(test_basic_string_destroy__inited_empty),\
    UT_CASE(test_basic_string_destroy__inited_non_empty),\
    UT_CASE_BEGIN(basic_string_c_str, test_basic_string_c_str__null_container),\
    UT_CASE(test_basic_string_c_str__non_inited_container),\
    UT_CASE(test_basic_string_c_str__empty),\
    UT_CASE(test_basic_string_c_str__non_empty),\
    UT_CASE_BEGIN(basic_string_data, test_basic_string_data__null_container),\
    UT_CASE(test_basic_string_data__non_inited_container),\
    UT_CASE(test_basic_string_data__empty),\
    UT_CASE(test_basic_string_data__non_empty),\
    UT_CASE_BEGIN(basic_string_copy, test_basic_string_copy__null_container),\
    UT_CASE(test_basic_string_copy__non_inited_container),\
    UT_CASE(test_basic_string_copy__null_buffer),\
    UT_CASE(test_basic_string_copy__invalid_position),\
    UT_CASE(test_basic_string_copy__begin_empty),\
    UT_CASE(test_basic_string_copy__begin_non_empty),\
    UT_CASE(test_basic_string_copy__begin_length),\
    UT_CASE(test_basic_string_copy__begin_npos),\
    UT_CASE(test_basic_string_copy__middle_empty),\
    UT_CASE(test_basic_string_copy__middle_non_empty),\
    UT_CASE(test_basic_string_copy__middle_length),\
    UT_CASE(test_basic_string_copy__middle_npos),\
    UT_CASE(test_basic_string_copy__end),\
    UT_CASE(test_basic_string_copy__npos),\
    UT_CASE_BEGIN(basic_string_size, test_basic_string_size__null_basic_string_container),\
    UT_CASE(test_basic_string_size__non_inited),\
    UT_CASE(test_basic_string_size__successfully_empty),\
    UT_CASE(test_basic_string_size__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_length, test_basic_string_length__null_basic_string_container),\
    UT_CASE(test_basic_string_length__non_inited),\
    UT_CASE(test_basic_string_length__successfully_empty),\
    UT_CASE(test_basic_string_length__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_empty, test_basic_string_empty__null_basic_string_container),\
    UT_CASE(test_basic_string_empty__non_inited),\
    UT_CASE(test_basic_string_empty__successfully_empty),\
    UT_CASE(test_basic_string_empty__successfully_non_empty),\
    UT_CASE_BEGIN(basic_string_max_size, test_basic_string_max_size__null_basic_string_container),\
    UT_CASE(test_basic_string_max_size__non_inited),\
    UT_CASE(test_basic_string_max_size__successfully),\
    UT_CASE_BEGIN(basic_string_capacity, test_basic_string_capacity__null_basic_string_container),\
    UT_CASE(test_basic_string_capacity__non_inited),\
    UT_CASE(test_basic_string_capacity__successfully_empty),\
    UT_CASE(test_basic_string_capacity__successfully_little),\
    UT_CASE(test_basic_string_capacity__successfully_huge),\
    UT_CASE_BEGIN(basic_string_at, test_basic_string_at__null_basic_string_container),\
    UT_CASE(test_basic_string_at__non_inited_basic_string_container),\
    UT_CASE(test_basic_string_at__invalid_subscript_empty),\
    UT_CASE(test_basic_string_at__invalid_subscript_end),\
    UT_CASE(test_basic_string_at__invalid_subscript),\
    UT_CASE(test_basic_string_at__successfully),\
    UT_CASE(test_basic_string_at__successfully_cstr)

#endif /* _UT_CSTL_BASIC_STRING_H_ */

