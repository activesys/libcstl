#ifndef _UT_CSTL_DEQUE_PRIVATE_H_
#define _UT_CSTL_DEQUE_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_deque_private)

/*
 * test _create_deque
 */
UT_CASE_DECLARATION(_create_deque)
void test__create_deque__null_typename(void** state);
void test__create_deque__unregisted_type(void** state);
void test__create_deque__c_builtin_type(void** state);
void test__create_deque__libcstl_builtin_type(void** state);
void test__create_deque__user_defined_type(void** state);
void test__create_deque__user_defined_type_dup(void** state);
/*
 * test _create_deque_auxiliary
 */
UT_CASE_DECLARATION(_create_deque_auxiliary)
void test__create_deque_auxiliary__null_deque_container(void** state);
void test__create_deque_auxiliary__null_typename(void** state);
void test__create_deque_auxiliary__unregisted_type(void** state);
void test__create_deque_auxiliary__c_builtin(void** state);
void test__create_deque_auxiliary__libcstl_builtin(void** state);
void test__create_deque_auxiliary__user_defined(void** state);
void test__create_deque_auxiliary__user_defined_dup(void** state);
/*
 * test _deque_init_elem and _deque_init_elem_varg
 */
UT_CASE_DECLARATION(_deque_init_elem__deque_init_elem_varg)
void test__deque_init_elem__deque_init_elem_varg__null_deque_container(void** state);
void test__deque_init_elem__deque_init_elem_varg__non_created_deque_container(void** state);
void test__deque_init_elem__deque_init_elem_varg__0_count(void** state);
void test__deque_init_elem__deque_init_elem_varg__count(void** state);
void test__deque_init_elem__deque_init_elem_varg__multiple_elem(void** state);
void test__deque_init_elem__deque_init_elem_varg__one_chunk(void** state);
void test__deque_init_elem__deque_init_elem_varg__more_than_one_chunk(void** state);
void test__deque_init_elem__deque_init_elem_varg__map_grow(void** state);
/*
 * test _deque_destroy_auxiliary
 */
UT_CASE_DECLARATION(_deque_destroy_auxiliary)
void test__deque_destroy_auxiliary__null_deque_container(void** state);
void test__deque_destroy_auxiliary__non_created_deque_container(void** state);
void test__deque_destroy_auxiliary__non_inited(void** state);
void test__deque_destroy_auxiliary__empty(void** state);
void test__deque_destroy_auxiliary__non_empty(void** state);
/*
 * test _deque_assign_elem and _deque_assign_elem_varg
 */
UT_CASE_DECLARATION(_deque_assign_elem__deque_assign_elem_varg)
void test__deque_assign_elem__deque_assign_elem_varg__null_deque_container(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__non_inited_deque_container(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__0_assign_0(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__0_assign_n(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__n_assign_0(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_greater_than_m(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_equal_to_m(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m(void** state);
void test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state);
/*
 * test _deque_push_back and _deque_push_back_varg
 */
UT_CASE_DECLARATION(_deque_push_back__deque_push_back_varg)
void test__deque_push_back__deque_push_back_varg__null_deque_container(void** state);
void test__deque_push_back__deque_push_back_varg__non_inited_deque_container(void** state);
void test__deque_push_back__deque_push_back_varg__empty(void** state);
void test__deque_push_back__deque_push_back_varg__non_empty(void** state);
void test__deque_push_back__deque_push_back_varg__non_empty_multiple(void** state);
/*
 * test _deque_push_front and _deque_push_front_varg
 */
UT_CASE_DECLARATION(_deque_push_front__deque_push_front_varg)
void test__deque_push_front__deque_push_front_varg__null_deque_container(void** state);
void test__deque_push_front__deque_push_front_varg__non_inited_deque_container(void** state);
void test__deque_push_front__deque_push_front_varg__empty(void** state);
void test__deque_push_front__deque_push_front_varg__non_empty(void** state);
void test__deque_push_front__deque_push_front_varg__non_empty_multiple(void** state);
/*
 * test _deque_resize_elem and _deque_resize_elem_varg
 */
UT_CASE_DECLARATION(_deque_resize_elem__deque_resize_elem_varg)
void test__deque_resize_elem__deque_resize_elem_varg__null_deque_container(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__non_inited_deque_container(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__0_resize_0(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__0_resize_n(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__n_resize_0(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_greater_than_m(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_equal_to_m(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m(void** state);
void test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state);
/*
 * test _deque_insert_n and _deque_insert_n_varg
 */
UT_CASE_DECLARATION(_deque_insert_n__deque_insert_n_varg)
void test__deque_insert_n__deque_insert_n_varg__null_deque_container(void** state);
void test__deque_insert_n__deque_insert_n_varg__non_inited_deque_container(void** state);
void test__deque_insert_n__deque_insert_n_varg__invalid_pos(void** state);
void test__deque_insert_n__deque_insert_n_varg__0_insert_0(void** state);
void test__deque_insert_n__deque_insert_n_varg__0_insert_n(void** state);
void test__deque_insert_n__deque_insert_n_varg__n_insert_0(void** state);
void test__deque_insert_n__deque_insert_n_varg__n_insert_begin(void** state);
void test__deque_insert_n__deque_insert_n_varg__n_insert_middle(void** state);
void test__deque_insert_n__deque_insert_n_varg__n_insert_end(void** state);
void test__deque_insert_n__deque_insert_n_varg__n_insert_end_multiple(void** state);
/*
 * test _deque_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_deque_init_elem_auxiliary)
void test__deque_init_elem_auxiliary__null_deque_container(void** state);
void test__deque_init_elem_auxiliary__null_elem(void** state);
void test__deque_init_elem_auxiliary__non_inited_deque(void** state);
void test__deque_init_elem_auxiliary__successfully_int(void** state);
void test__deque_init_elem_auxiliary__successfully_cstr(void** state);
void test__deque_init_elem_auxiliary__successfully_iterator(void** state);
void test__deque_init_elem_auxiliary__successfully_container(void** state);
void test__deque_init_elem_auxiliary__successfully_user_defined(void** state);

#define UT_CSTL_DEQUE_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_deque_private, test__create_deque__null_typename),\
    UT_CASE(test__create_deque__unregisted_type),\
    UT_CASE(test__create_deque__c_builtin_type),\
    UT_CASE(test__create_deque__libcstl_builtin_type),\
    UT_CASE(test__create_deque__user_defined_type),\
    UT_CASE(test__create_deque__user_defined_type_dup),\
    UT_CASE_BEGIN(_create_deque_auxiliary, test__create_deque_auxiliary__null_deque_container),\
    UT_CASE(test__create_deque_auxiliary__null_typename),\
    UT_CASE(test__create_deque_auxiliary__unregisted_type),\
    UT_CASE(test__create_deque_auxiliary__c_builtin),\
    UT_CASE(test__create_deque_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_deque_auxiliary__user_defined),\
    UT_CASE(test__create_deque_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_deque_init_elem__deque_init_elem_varg, test__deque_init_elem__deque_init_elem_varg__null_deque_container),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__non_created_deque_container),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__0_count),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__count),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__multiple_elem),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__one_chunk),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__more_than_one_chunk),\
    UT_CASE(test__deque_init_elem__deque_init_elem_varg__map_grow),\
    UT_CASE_BEGIN(_deque_destroy_auxiliary, test__deque_destroy_auxiliary__null_deque_container),\
    UT_CASE(test__deque_destroy_auxiliary__non_created_deque_container),\
    UT_CASE(test__deque_destroy_auxiliary__non_inited),\
    UT_CASE(test__deque_destroy_auxiliary__empty),\
    UT_CASE(test__deque_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_deque_assign_elem__deque_assign_elem_varg,\
        test__deque_assign_elem__deque_assign_elem_varg__null_deque_container),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__non_inited_deque_container),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__0_assign_0),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__0_assign_n),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__n_assign_0),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_greater_than_m),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_equal_to_m),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m),\
    UT_CASE(test__deque_assign_elem__deque_assign_elem_varg__n_assign_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_deque_push_back__deque_push_back_varg,\
        test__deque_push_back__deque_push_back_varg__null_deque_container),\
    UT_CASE(test__deque_push_back__deque_push_back_varg__non_inited_deque_container),\
    UT_CASE(test__deque_push_back__deque_push_back_varg__empty),\
    UT_CASE(test__deque_push_back__deque_push_back_varg__non_empty),\
    UT_CASE(test__deque_push_back__deque_push_back_varg__non_empty_multiple),\
    UT_CASE_BEGIN(_deque_push_front__deque_push_front_varg,\
        test__deque_push_front__deque_push_front_varg__null_deque_container),\
    UT_CASE(test__deque_push_front__deque_push_front_varg__non_inited_deque_container),\
    UT_CASE(test__deque_push_front__deque_push_front_varg__empty),\
    UT_CASE(test__deque_push_front__deque_push_front_varg__non_empty),\
    UT_CASE(test__deque_push_front__deque_push_front_varg__non_empty_multiple),\
    UT_CASE_BEGIN(_deque_resize_elem__deque_resize_elem_varg,\
        test__deque_resize_elem__deque_resize_elem_varg__null_deque_container),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__non_inited_deque_container),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__0_resize_0),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__0_resize_n),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__n_resize_0),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_greater_than_m),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_equal_to_m),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m),\
    UT_CASE(test__deque_resize_elem__deque_resize_elem_varg__n_resize_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_deque_insert_n__deque_insert_n_varg, test__deque_insert_n__deque_insert_n_varg__null_deque_container),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__non_inited_deque_container),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__invalid_pos),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__0_insert_0),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__0_insert_n),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__n_insert_0),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__n_insert_begin),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__n_insert_middle),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__n_insert_end),\
    UT_CASE(test__deque_insert_n__deque_insert_n_varg__n_insert_end_multiple),\
    UT_CASE_BEGIN(_deque_init_elem_auxiliary, test__deque_init_elem_auxiliary__null_deque_container),\
    UT_CASE(test__deque_init_elem_auxiliary__null_elem),\
    UT_CASE(test__deque_init_elem_auxiliary__non_inited_deque),\
    UT_CASE(test__deque_init_elem_auxiliary__successfully_int),\
    UT_CASE(test__deque_init_elem_auxiliary__successfully_cstr),\
    UT_CASE(test__deque_init_elem_auxiliary__successfully_iterator),\
    UT_CASE(test__deque_init_elem_auxiliary__successfully_container),\
    UT_CASE(test__deque_init_elem_auxiliary__successfully_user_defined)

#endif /* _UT_CSTL_DEQUE_PRIVATE_H_ */

