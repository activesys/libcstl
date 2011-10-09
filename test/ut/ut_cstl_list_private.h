#ifndef _UT_CSTL_LIST_PRIVATE_H_
#define _UT_CSTL_LIST_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_list_private)

/*
 * test _create_list
 */
UT_CASE_DECLARATION(_create_list)
void test__create_list__null_typename(void** state);
void test__create_list__unregisted_type(void** state);
void test__create_list__c_builtin_type(void** state);
void test__create_list__libcstl_builtin_type(void** state);
void test__create_list__user_defined_type(void** state);
void test__create_list__user_defined_type_dup(void** state);
/*
 * test _create_list_auxiliary
 */
UT_CASE_DECLARATION(_create_list_auxiliary)
void test__create_list_auxiliary__null_list_container(void** state);
void test__create_list_auxiliary__null_typename(void** state);
void test__create_list_auxiliary__unregisted_type(void** state);
void test__create_list_auxiliary__c_builtin(void** state);
void test__create_list_auxiliary__libcstl_builtin(void** state);
void test__create_list_auxiliary__user_defined(void** state);
void test__create_list_auxiliary__user_defined_dup(void** state);
/*
 * test _list_init_elem and _list_init_elem_varg
 */
UT_CASE_DECLARATION(_list_init_elem__list_init_elem_varg)
void test__list_init_elem__list_init_elem_varg__null_list_container(void** state);
void test__list_init_elem__list_init_elem_varg__non_created_list_container(void** state);
void test__list_init_elem__list_init_elem_varg__0_count(void** state);
void test__list_init_elem__list_init_elem_varg__count(void** state);
void test__list_init_elem__list_init_elem_varg__multiple_elem(void** state);
/*
 * test _list_destroy_auxiliary
 */
UT_CASE_DECLARATION(_list_destroy_auxiliary)
void test__list_destroy_auxiliary__null_list_container(void** state);
void test__list_destroy_auxiliary__non_created_list_container(void** state);
void test__list_destroy_auxiliary__non_inited(void** state);
void test__list_destroy_auxiliary__empty(void** state);
void test__list_destroy_auxiliary__non_empty(void** state);
/*
 * test _list_assign_elem and _list_assign_elem_varg
 */
UT_CASE_DECLARATION(_list_assign_elem__list_assign_elem_varg)
void test__list_assign_elem__list_assign_elem_varg__null_list_container(void** state);
void test__list_assign_elem__list_assign_elem_varg__non_inited_list_container(void** state);
void test__list_assign_elem__list_assign_elem_varg__0_assign_0(void** state);
void test__list_assign_elem__list_assign_elem_varg__0_assign_n(void** state);
void test__list_assign_elem__list_assign_elem_varg__n_assign_0(void** state);
void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_greater_than_m(void** state);
void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_equal_to_m(void** state);
void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m(void** state);
void test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state);
/*
 * test _list_push_back and _list_push_back_varg
 */
UT_CASE_DECLARATION(_list_push_back__list_push_back_varg)
void test__list_push_back__list_push_back_varg__null_list_container(void** state);
void test__list_push_back__list_push_back_varg__non_inited_list_container(void** state);
void test__list_push_back__list_push_back_varg__empty(void** state);
void test__list_push_back__list_push_back_varg__non_empty(void** state);
void test__list_push_back__list_push_back_varg__non_empty_multiple(void** state);
/*
 * test _list_push_front and _list_push_front_varg
 */
UT_CASE_DECLARATION(_list_push_front__list_push_front_varg)
void test__list_push_front__list_push_front_varg__null_list_container(void** state);
void test__list_push_front__list_push_front_varg__non_inited_list_container(void** state);
void test__list_push_front__list_push_front_varg__empty(void** state);
void test__list_push_front__list_push_front_varg__non_empty(void** state);
void test__list_push_front__list_push_front_varg__non_empty_multiple(void** state);
/*
 * test _list_resize_elem and _list_resize_elem_varg
 */
UT_CASE_DECLARATION(_list_resize_elem__list_resize_elem_varg)
void test__list_resize_elem__list_resize_elem_varg__null_list_container(void** state);
void test__list_resize_elem__list_resize_elem_varg__non_inited_list_container(void** state);
void test__list_resize_elem__list_resize_elem_varg__0_resize_0(void** state);
void test__list_resize_elem__list_resize_elem_varg__0_resize_n(void** state);
void test__list_resize_elem__list_resize_elem_varg__n_resize_0(void** state);
void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_greater_than_m(void** state);
void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_equal_to_m(void** state);
void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m(void** state);
void test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state);
/*
 * test _list_remove and _list_remove_varg
 */
UT_CASE_DECLARATION(_list_remove__list_remove_varg)
void test__list_remove__list_remove_varg__null_list_container(void** state);
void test__list_remove__list_remove_varg__non_inited_list_container(void** state);
void test__list_remove__list_remove_varg__empty(void** state);
void test__list_remove__list_remove_varg__non_empty_no_removed(void** state);
void test__list_remove__list_remove_varg__non_empty_remove(void** state);
void test__list_remove__list_remove_varg__non_empty_remove_more(void** state);
void test__list_remove__list_remove_varg__non_empty_remove_more_multiple(void** state);
/*
 * test _list_insert_n and _list_insert_n_varg
 */
UT_CASE_DECLARATION(_list_insert_n__list_insert_n_varg)
void test__list_insert_n__list_insert_n_varg__null_list_container(void** state);
void test__list_insert_n__list_insert_n_varg__non_inited_list_container(void** state);
void test__list_insert_n__list_insert_n_varg__invalid_pos(void** state);
void test__list_insert_n__list_insert_n_varg__0_insert_0(void** state);
void test__list_insert_n__list_insert_n_varg__0_insert_n(void** state);
void test__list_insert_n__list_insert_n_varg__n_insert_0(void** state);
void test__list_insert_n__list_insert_n_varg__n_insert_begin(void** state);
void test__list_insert_n__list_insert_n_varg__n_insert_middle(void** state);
void test__list_insert_n__list_insert_n_varg__n_insert_end(void** state);
void test__list_insert_n__list_insert_n_varg__n_insert_end_multiple(void** state);
/*
 * test _list_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_list_init_elem_auxiliary)
void test__list_init_elem_auxiliary__null_list_container(void** state);
void test__list_init_elem_auxiliary__null_elem(void** state);
void test__list_init_elem_auxiliary__non_inited_list(void** state);
void test__list_init_elem_auxiliary__successfully_int(void** state);
void test__list_init_elem_auxiliary__successfully_cstr(void** state);
void test__list_init_elem_auxiliary__successfully_iterator(void** state);
void test__list_init_elem_auxiliary__successfully_container(void** state);
void test__list_init_elem_auxiliary__successfully_user_defined(void** state);

#define UT_CSTL_LIST_PRIVATE_CASE \
    UT_SUIT_BEGIN(cstl_list_private, test__create_list__null_typename),\
    UT_CASE(test__create_list__unregisted_type),\
    UT_CASE(test__create_list__c_builtin_type),\
    UT_CASE(test__create_list__libcstl_builtin_type),\
    UT_CASE(test__create_list__user_defined_type),\
    UT_CASE(test__create_list__user_defined_type_dup),\
    UT_CASE_BEGIN(_create_list_auxiliary, test__create_list_auxiliary__null_list_container),\
    UT_CASE(test__create_list_auxiliary__null_typename),\
    UT_CASE(test__create_list_auxiliary__unregisted_type),\
    UT_CASE(test__create_list_auxiliary__c_builtin),\
    UT_CASE(test__create_list_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_list_auxiliary__user_defined),\
    UT_CASE(test__create_list_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_list_init_elem__list_init_elem_varg,\
        test__list_init_elem__list_init_elem_varg__null_list_container),\
    UT_CASE(test__list_init_elem__list_init_elem_varg__non_created_list_container),\
    UT_CASE(test__list_init_elem__list_init_elem_varg__0_count),\
    UT_CASE(test__list_init_elem__list_init_elem_varg__count),\
    UT_CASE(test__list_init_elem__list_init_elem_varg__multiple_elem),\
    UT_CASE_BEGIN(_list_destroy_auxiliary, test__list_destroy_auxiliary__null_list_container),\
    UT_CASE(test__list_destroy_auxiliary__non_created_list_container),\
    UT_CASE(test__list_destroy_auxiliary__non_inited),\
    UT_CASE(test__list_destroy_auxiliary__empty),\
    UT_CASE(test__list_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_list_assign_elem__list_assign_elem_varg,\
        test__list_assign_elem__list_assign_elem_varg__null_list_container),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__non_inited_list_container),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__0_assign_0),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__0_assign_n),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__n_assign_0),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_greater_than_m),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_equal_to_m),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m),\
    UT_CASE(test__list_assign_elem__list_assign_elem_varg__n_assign_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_list_push_back__list_push_back_varg,\
        test__list_push_back__list_push_back_varg__null_list_container),\
    UT_CASE(test__list_push_back__list_push_back_varg__non_inited_list_container),\
    UT_CASE(test__list_push_back__list_push_back_varg__empty),\
    UT_CASE(test__list_push_back__list_push_back_varg__non_empty),\
    UT_CASE(test__list_push_back__list_push_back_varg__non_empty_multiple),\
    UT_CASE_BEGIN(_list_push_front__list_push_front_varg,\
        test__list_push_front__list_push_front_varg__null_list_container),\
    UT_CASE(test__list_push_front__list_push_front_varg__non_inited_list_container),\
    UT_CASE(test__list_push_front__list_push_front_varg__empty),\
    UT_CASE(test__list_push_front__list_push_front_varg__non_empty),\
    UT_CASE(test__list_push_front__list_push_front_varg__non_empty_multiple),\
    UT_CASE_BEGIN(_list_resize_elem__list_resize_elem_varg,\
        test__list_resize_elem__list_resize_elem_varg__null_list_container),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__non_inited_list_container),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__0_resize_0),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__0_resize_n),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__n_resize_0),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_greater_than_m),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_equal_to_m),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m),\
    UT_CASE(test__list_resize_elem__list_resize_elem_varg__n_resize_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_list_remove__list_remove_varg, test__list_remove__list_remove_varg__null_list_container),\
    UT_CASE(test__list_remove__list_remove_varg__non_inited_list_container),\
    UT_CASE(test__list_remove__list_remove_varg__empty),\
    UT_CASE(test__list_remove__list_remove_varg__non_empty_no_removed),\
    UT_CASE(test__list_remove__list_remove_varg__non_empty_remove),\
    UT_CASE(test__list_remove__list_remove_varg__non_empty_remove_more),\
    UT_CASE(test__list_remove__list_remove_varg__non_empty_remove_more_multiple),\
    UT_CASE_BEGIN(_list_insert_n__list_insert_n_varg, test__list_insert_n__list_insert_n_varg__null_list_container),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__non_inited_list_container),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__invalid_pos),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__0_insert_0),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__0_insert_n),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__n_insert_0),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__n_insert_begin),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__n_insert_middle),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__n_insert_end),\
    UT_CASE(test__list_insert_n__list_insert_n_varg__n_insert_end_multiple),\
    UT_CASE_BEGIN(_list_init_elem_auxiliary, test__list_init_elem_auxiliary__null_list_container),\
    UT_CASE(test__list_init_elem_auxiliary__null_elem),\
    UT_CASE(test__list_init_elem_auxiliary__non_inited_list),\
    UT_CASE(test__list_init_elem_auxiliary__successfully_int),\
    UT_CASE(test__list_init_elem_auxiliary__successfully_cstr),\
    UT_CASE(test__list_init_elem_auxiliary__successfully_iterator),\
    UT_CASE(test__list_init_elem_auxiliary__successfully_container),\
    UT_CASE(test__list_init_elem_auxiliary__successfully_user_defined)

#endif /* _UT_CSTL_LIST_PRIVATE_H_ */

