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
/*
 * test _create_vector_auxiliary
 */
UT_CASE_DECLARATION(_create_vector_auxiliary)
void test__create_vector_auxiliary__null_vector_container(void** state);
void test__create_vector_auxiliary__null_typename(void** state);
void test__create_vector_auxiliary__unregisted_type(void** state);
void test__create_vector_auxiliary__c_builtin_type(void** state);
void test__create_vector_auxiliary__libcstl_builtin_type(void** state);
void test__create_vector_auxiliary__registed_type(void** state);
/*
 * test _vector_init_elem and _vector_init_elem_varg
 */
UT_CASE_DECLARATION(_vector_init_elem__vector_init_elem_varg)
void test__vector_init_elem__vector_init_elem_varg__null_vector_container(void** state);
void test__vector_init_elem__vector_init_elem_varg__non_created(void** state);
void test__vector_init_elem__vector_init_elem_varg__successfully_0_count(void** state);
void test__vector_init_elem__vector_init_elem_varg__successfully(void** state);
void test__vector_init_elem__vector_init_elem_varg__successfully_large_amounts_of_data(void** state);
void test__vector_init_elem__vector_init_elem_varg__successfully_multiple_specificed_element(void** state);
/*
 * test _vector_destroy_auxiliary
 */
UT_CASE_DECLARATION(_vector_destroy_auxiliary)
void test__vector_destroy_auxiliary__null_vector_container(void** state);
void test__vector_destroy_auxiliary__invalid_vector_container_finish_less_than_start(void** state);
void test__vector_destroy_auxiliary__invalid_vector_container_endofstorage_less_than_start(void** state);
void test__vector_destroy_auxiliary__successfully_non_init_container(void** state);
void test__vector_destroy_auxiliary__successfully_empty_container(void** state);
void test__vector_destroy_auxiliary__successfully(void** state);
/*
 * test _vector_assign_elem and _vector_assign_elem_varg
 */
UT_CASE_DECLARATION(_vector_assign_elem__vector_assign_elem_varg)
void test__vector_assign_elem__vector_assign_elem_varg__null_vector_container(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__non_inited(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_0_count(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_n_count(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_0_count(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count_n_less_than_m(void** state);
void test__vector_assign_elem__vector_assign_elem_varg__successfully_multiple_count(void** state);
/*
 * test _vector_push_back and _vector_push_back_varg
 */
UT_CASE_DECLARATION(_vector_push_back__vector_push_back_varg)
void test__vector_push_back__vector_push_back_varg__null_vector_container(void** state);
void test__vector_push_back__vector_push_back_varg__non_inited(void** state);
void test__vector_push_back__vector_push_back_varg__successfully_empty(void** state);
void test__vector_push_back__vector_push_back_varg__successfully_capacity_not_change(void** state);
void test__vector_push_back__vector_push_back_varg__successfully_capacity_change(void** state);
void test__vector_push_back__vector_push_back_varg__successfully_multiple_element(void** state);
/*
 * test _vector_resize_elem and _vector_resize_elem_varg
 */
UT_CASE_DECLARATION(_vector_resize_elem__vector_resize_elem_varg)
void test__vector_resize_elem__vector_resize_elem_varg__null_vector_container(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__non_inited(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_0(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_10(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_1000(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_0(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_10(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_1000(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_0(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_10(void** setate);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1000(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1200(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000(void** state);
void test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000_multiple(void** state);
/*
 * test _vector_insert_n and _vector_insert_n_varg
 */
UT_CASE_DECLARATION(_vector_insert_n__vector_insert_n_varg)
void test__vector_insert_n__vector_insert_n_varg__null_vector_container(void** state);
void test__vector_insert_n__vector_insert_n_varg__non_inited(void** state);
void test__vector_insert_n__vector_insert_n_varg__invalid_position(void** state);
void test__vector_insert_n__vector_insert_n_varg__empty_insert_0(void** state);
void test__vector_insert_n__vector_insert_n_varg__empty_insert_10(void** state);
void test__vector_insert_n__vector_insert_n_varg__empty_insert_1000(void** state);
void test__vector_insert_n__vector_insert_n_varg__begin_insert_0(void** state);
void test__vector_insert_n__vector_insert_n_varg__begin_insert_10(void** state);
void test__vector_insert_n__vector_insert_n_varg__begin_insert_1000(void** state);
void test__vector_insert_n__vector_insert_n_varg__middle_insert_0(void** state);
void test__vector_insert_n__vector_insert_n_varg__middle_insert_10(void** state);
void test__vector_insert_n__vector_insert_n_varg__middle_insert_1000(void** state);
void test__vector_insert_n__vector_insert_n_varg__end_insert_0(void** state);
void test__vector_insert_n__vector_insert_n_varg__end_insert_10(void** state);
void test__vector_insert_n__vector_insert_n_varg__end_insert_1000(void** state);
void test__vector_insert_n__vector_insert_n_varg__end_insert_1000_multiple(void** state);
/*
 * test _vector_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_vector_init_elem_auxiliary)
void test__vector_init_elem_auxiliary__null_vector_container(void** state);
void test__vector_init_elem_auxiliary__null_elem(void** state);
void test__vector_init_elem_auxiliary__non_created_vector(void** state);
void test__vector_init_elem_auxiliary__successfully_int(void** state);
void test__vector_init_elem_auxiliary__successfully_cstr(void** state);
void test__vector_init_elem_auxiliary__successfully_iterator(void** state);
void test__vector_init_elem_auxiliary__successfully_container(void** state);

#define UT_CSTL_VECTOR_PRIVATE_CASE \
    UT_SUIT_BEGIN(cstl_vector_private, test__create_vector__null_typename),\
    UT_CASE(test__create_vector__unregisted_type),\
    UT_CASE(test__create_vector__c_builtin_type),\
    UT_CASE(test__create_vector__libcstl_builtin_type),\
    UT_CASE(test__create_vector__registed_type),\
    UT_CASE_BEGIN(_create_vector_auxiliary, test__create_vector_auxiliary__null_vector_container),\
    UT_CASE(test__create_vector_auxiliary__null_typename),\
    UT_CASE(test__create_vector_auxiliary__unregisted_type),\
    UT_CASE(test__create_vector_auxiliary__c_builtin_type),\
    UT_CASE(test__create_vector_auxiliary__libcstl_builtin_type),\
    UT_CASE(test__create_vector_auxiliary__registed_type),\
    UT_CASE_BEGIN(_vector_init_elem__vector_init_elem_varg,\
            test__vector_init_elem__vector_init_elem_varg__null_vector_container),\
    UT_CASE(test__vector_init_elem__vector_init_elem_varg__non_created),\
    UT_CASE(test__vector_init_elem__vector_init_elem_varg__successfully_0_count),\
    UT_CASE(test__vector_init_elem__vector_init_elem_varg__successfully),\
    UT_CASE(test__vector_init_elem__vector_init_elem_varg__successfully_large_amounts_of_data),\
    UT_CASE(test__vector_init_elem__vector_init_elem_varg__successfully_multiple_specificed_element),\
    UT_CASE_BEGIN(_vector_destroy_auxiliary, test__vector_destroy_auxiliary__null_vector_container),\
    UT_CASE(test__vector_destroy_auxiliary__invalid_vector_container_finish_less_than_start),\
    UT_CASE(test__vector_destroy_auxiliary__invalid_vector_container_endofstorage_less_than_start),\
    UT_CASE(test__vector_destroy_auxiliary__successfully_non_init_container),\
    UT_CASE(test__vector_destroy_auxiliary__successfully_empty_container),\
    UT_CASE(test__vector_destroy_auxiliary__successfully),\
    UT_CASE_BEGIN(_vector_assign_elem__vector_assign_elem_varg, \
        test__vector_assign_elem__vector_assign_elem_varg__null_vector_container),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__non_inited),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_0_count),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_init_0_assign_n_count),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_0_count),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_init_n_assign_m_count_n_less_than_m),\
    UT_CASE(test__vector_assign_elem__vector_assign_elem_varg__successfully_multiple_count),\
    UT_CASE_BEGIN(_vector_push_back__vector_push_back_varg,\
        test__vector_push_back__vector_push_back_varg__null_vector_container),\
    UT_CASE(test__vector_push_back__vector_push_back_varg__non_inited),\
    UT_CASE(test__vector_push_back__vector_push_back_varg__successfully_empty),\
    UT_CASE(test__vector_push_back__vector_push_back_varg__successfully_capacity_not_change),\
    UT_CASE(test__vector_push_back__vector_push_back_varg__successfully_capacity_change),\
    UT_CASE(test__vector_push_back__vector_push_back_varg__successfully_multiple_element),\
    UT_CASE_BEGIN(_vector_resize_elem__vector_resize_elem_varg,\
        test__vector_resize_elem__vector_resize_elem_varg__null_vector_container),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__non_inited),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_0),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_10),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_0_resize_1000),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_0),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_10),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_10_resize_1000),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_0),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_10),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1000),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_1200),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000),\
    UT_CASE(test__vector_resize_elem__vector_resize_elem_varg__successfully_1000_resize_2000_multiple),\
    UT_CASE_BEGIN(_vector_insert_n__vector_insert_n_varg,\
        test__vector_insert_n__vector_insert_n_varg__null_vector_container),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__non_inited),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__invalid_position),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__empty_insert_0),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__empty_insert_10),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__empty_insert_1000),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__begin_insert_0),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__begin_insert_10),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__begin_insert_1000),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__middle_insert_0),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__middle_insert_10),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__middle_insert_1000),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__end_insert_0),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__end_insert_10),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__end_insert_1000),\
    UT_CASE(test__vector_insert_n__vector_insert_n_varg__end_insert_1000_multiple),\
    UT_CASE_BEGIN(_vector_init_elem_auxiliary, test__vector_init_elem_auxiliary__null_vector_container),\
    UT_CASE(test__vector_init_elem_auxiliary__null_elem),\
    UT_CASE(test__vector_init_elem_auxiliary__non_created_vector),\
    UT_CASE(test__vector_init_elem_auxiliary__successfully_int),\
    UT_CASE(test__vector_init_elem_auxiliary__successfully_cstr),\
    UT_CASE(test__vector_init_elem_auxiliary__successfully_iterator),\
    UT_CASE(test__vector_init_elem_auxiliary__successfully_container)

#endif /* _UT_CSTL_VECTOR_PRIVATE_H_ */

