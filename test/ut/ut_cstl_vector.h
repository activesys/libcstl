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
/*
 * test vector_init_copy
 */
UT_CASE_DECLARATION(vector_init_copy)
void test_vector_init_copy__null_dest(void** state);
void test_vector_init_copy__null_src(void** state);
void test_vector_init_copy__non_create_dest(void** state);
void test_vector_init_copy__non_inited_src(void** state);
void test_vector_init_copy__not_same_type(void** state);
void test_vector_init_copy__successfully_c_builtin_empty(void** state);
void test_vector_init_copy__successfully_c_builtin_little(void** state);
void test_vector_init_copy__successfully_c_builtin_huge(void** state);
void test_vector_init_copy__successfully_cstr_empty(void** state);
void test_vector_init_copy__successfully_cstr_little(void** state);
void test_vector_init_copy__successfully_cstr_huge(void** state);
void test_vector_init_copy__successfully_cstl_builtin_empty(void** state);
void test_vector_init_copy__successfully_cstl_builtin_little(void** state);
void test_vector_init_copy__successfully_cstl_builtin_huge(void** state);
void test_vector_init_copy__successfully_user_define_empty(void** state);
void test_vector_init_copy__successfully_user_define_little(void** state);
void test_vector_init_copy__successfully_user_define_huge(void** state);
/*
 * test vector_init_copy_range
 */
UT_CASE_DECLARATION(vector_init_copy_range)
void test_vector_init_copy_range__null_dest(void** state);
void test_vector_init_copy_range__invalid_begin_iterator(void** state);
void test_vector_init_copy_range__invalid_end_iterator(void** state);
void test_vector_init_copy_range__invalid_range(void** state);
void test_vector_init_copy_range__not_same_type(void** state);
void test_vector_init_copy_range__successfully_empty_range(void** state);
void test_vector_init_copy_range__successfully_c_builtin(void** state);
void test_vector_init_copy_range__successfully_cstr(void** state);
void test_vector_init_copy_range__successfully_cstl_builtin(void** state);
void test_vector_init_copy_range__successfully_user_define(void** state);
/*
 * test vector_destroy
 */
UT_CASE_DECLARATION(vector_destroy)
void test_vector_destroy__null_vector_container(void** state);
void test_vector_destroy__non_created(void** state);
void test_vector_destroy__created_non_inited(void** state);
void test_vector_destroy__inited_empty(void** state);
void test_vector_destroy__inited_non_empty(void** state);

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
    UT_CASE(test_vector_init_n__successfully_user_defined),\
    UT_CASE_BEGIN(vector_init_copy, test_vector_init_copy__null_dest),\
    UT_CASE(test_vector_init_copy__null_src),\
    UT_CASE(test_vector_init_copy__non_create_dest),\
    UT_CASE(test_vector_init_copy__non_inited_src),\
    UT_CASE(test_vector_init_copy__not_same_type),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_empty),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_little),\
    UT_CASE(test_vector_init_copy__successfully_c_builtin_huge),\
    UT_CASE(test_vector_init_copy__successfully_cstr_empty),\
    UT_CASE(test_vector_init_copy__successfully_cstr_little),\
    UT_CASE(test_vector_init_copy__successfully_cstr_huge),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_empty),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_little),\
    UT_CASE(test_vector_init_copy__successfully_cstl_builtin_huge),\
    UT_CASE(test_vector_init_copy__successfully_user_define_empty),\
    UT_CASE(test_vector_init_copy__successfully_user_define_little),\
    UT_CASE(test_vector_init_copy__successfully_user_define_huge),\
    UT_CASE_BEGIN(vector_init_copy_range, test_vector_init_copy_range__null_dest),\
    UT_CASE(test_vector_init_copy_range__invalid_begin_iterator),\
    UT_CASE(test_vector_init_copy_range__invalid_end_iterator),\
    UT_CASE(test_vector_init_copy_range__invalid_range),\
    UT_CASE(test_vector_init_copy_range__not_same_type),\
    UT_CASE(test_vector_init_copy_range__successfully_empty_range),\
    UT_CASE(test_vector_init_copy_range__successfully_c_builtin),\
    UT_CASE(test_vector_init_copy_range__successfully_cstr),\
    UT_CASE(test_vector_init_copy_range__successfully_cstl_builtin),\
    UT_CASE(test_vector_init_copy_range__successfully_user_define),\
    UT_CASE_BEGIN(vector_destroy, test_vector_destroy__null_vector_container),\
    UT_CASE(test_vector_destroy__non_created),\
    UT_CASE(test_vector_destroy__created_non_inited),\
    UT_CASE(test_vector_destroy__inited_empty),\
    UT_CASE(test_vector_destroy__inited_non_empty)

#endif /* _UT_CSTL_VECTOR_H_ */

