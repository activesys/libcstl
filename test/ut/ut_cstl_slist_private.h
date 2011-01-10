#ifndef _UT_CSTL_SLIST_PRIVATE_H_
#define _UT_CSTL_SLIST_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_slist_private)

/*
 * test _create_slist
 */
UT_CASE_DECLARATION(_create_slist)
void test__create_slist__null_typename(void** state);
void test__create_slist__unregisted_type(void** state);
void test__create_slist__c_builtin_type(void** state);
void test__create_slist__libcstl_builtin_type(void** state);
void test__create_slist__user_defined_type(void** state);
void test__create_slist__user_defined_type_dup(void** state);
/*
 * test _create_slist_auxiliary
 */
UT_CASE_DECLARATION(_create_slist_auxiliary)
void test__create_slist_auxiliary__null_slist_container(void** state);
void test__create_slist_auxiliary__null_typename(void** state);
void test__create_slist_auxiliary__unregisted_type(void** state);
void test__create_slist_auxiliary__c_builtin(void** state);
void test__create_slist_auxiliary__libcstl_builtin(void** state);
void test__create_slist_auxiliary__user_defined(void** state);
void test__create_slist_auxiliary__user_defined_dup(void** state);
/*
 * test _slist_init_elem and _slist_init_elem_varg
 */
UT_CASE_DECLARATION(_slist_init_elem__slist_init_elem_varg)
void test__slist_init_elem__slist_init_elem_varg__null_slist_container(void** state);
void test__slist_init_elem__slist_init_elem_varg__non_created_slist_container(void** state);
void test__slist_init_elem__slist_init_elem_varg__0_count(void** state);
void test__slist_init_elem__slist_init_elem_varg__count(void** state);
void test__slist_init_elem__slist_init_elem_varg__multiple_elem(void** state);
/*
 * test _slist_destroy_auxiliary
 */
UT_CASE_DECLARATION(_slist_destroy_auxiliary)
void test__slist_destroy_auxiliary__null_slist_container(void** state);
void test__slist_destroy_auxiliary__non_created_slist_container(void** state);
void test__slist_destroy_auxiliary__non_inited(void** state);
void test__slist_destroy_auxiliary__empty(void** state);
void test__slist_destroy_auxiliary__non_empty(void** state);
/*
 * test _slist_assign_elem and _slist_assign_elem_varg
 */
UT_CASE_DECLARATION(_slist_assign_elem__slist_assign_elem_varg)
void test__slist_assign_elem__slist_assign_elem_varg__null_slist_container(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__non_inited_slist_container(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__0_assign_0(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__0_assign_n(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__n_assign_0(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_greater_than_m(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_equal_to_m(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m(void** state);
void test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m_multiple(void** state);
/*
 * test _slist_push_front and _slist_push_front_varg
 */
UT_CASE_DECLARATION(_slist_push_front__slist_push_front_varg)
void test__slist_push_front__slist_push_front_varg__null_slist_container(void** state);
void test__slist_push_front__slist_push_front_varg__non_inited_slist_container(void** state);
void test__slist_push_front__slist_push_front_varg__empty(void** state);
void test__slist_push_front__slist_push_front_varg__non_empty(void** state);
void test__slist_push_front__slist_push_front_varg__non_empty_multiple(void** state);
/*
 * test _slist_resize_elem and _slist_resize_elem_varg
 */
UT_CASE_DECLARATION(_slist_resize_elem__slist_resize_elem_varg)
void test__slist_resize_elem__slist_resize_elem_varg__null_slist_container(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__non_inited_slist_container(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__0_resize_0(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__0_resize_n(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__n_resize_0(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_greater_than_m(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_equal_to_m(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m(void** state);
void test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m_multiple(void** state);
/*
 * test _slist_remove and _slist_remove_varg
 */
UT_CASE_DECLARATION(_slist_remove__slist_remove_varg)
void test__slist_remove__slist_remove_varg__null_slist_container(void** state);
void test__slist_remove__slist_remove_varg__non_inited_slist_container(void** state);
void test__slist_remove__slist_remove_varg__empty(void** state);
void test__slist_remove__slist_remove_varg__non_empty_no_removed(void** state);
void test__slist_remove__slist_remove_varg__non_empty_remove(void** state);
void test__slist_remove__slist_remove_varg__non_empty_remove_more(void** state);
void test__slist_remove__slist_remove_varg__non_empty_remove_more_multiple(void** state);
/*
 * test _slist_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_slist_init_elem_auxiliary)
void test__slist_init_elem_auxiliary__null_slist_container(void** state);
void test__slist_init_elem_auxiliary__null_elem(void** state);
void test__slist_init_elem_auxiliary__non_inited_slist(void** state);
void test__slist_init_elem_auxiliary__successfully_int(void** state);
void test__slist_init_elem_auxiliary__successfully_cstr(void** state);
void test__slist_init_elem_auxiliary__successfully_iterator(void** state);
void test__slist_init_elem_auxiliary__successfully_container(void** state);
void test__slist_init_elem_auxiliary__successfully_user_defined(void** state);
/*
 * test _slist_insert
 */
UT_CASE_DECLARATION(_slist_insert)
void test__slist_insert__null_slist_container(void** state);
void test__slist_insert__non_inited_slist_container(void** state);
void test__slist_insert__invalid_pos(void** state);
void test__slist_insert__empty_insert(void** state);
void test__slist_insert__n_insert_begin(void** state);
void test__slist_insert__n_insert_middle(void** state);
void test__slist_insert__n_insert_end(void** state);
void test__slist_insert__n_insert_end_multiple(void** state);
/*
 * test _slist_insert_n
 */
UT_CASE_DECLARATION(_slist_insert_n)
void test__slist_insert_n__null_slist_container(void** state);
void test__slist_insert_n__non_inited_slist_container(void** state);
void test__slist_insert_n__invalid_pos(void** state);
void test__slist_insert_n__0_insert_0(void** state);
void test__slist_insert_n__0_insert_n(void** state);
void test__slist_insert_n__n_insert_0(void** state);
void test__slist_insert_n__n_insert_begin(void** state);
void test__slist_insert_n__n_insert_middle(void** state);
void test__slist_insert_n__n_insert_end(void** state);
void test__slist_insert_n__n_insert_end_multiple(void** state);
/*
 * test _slist_insert_after
 */
UT_CASE_DECLARATION(_slist_insert_after)
void test__slist_insert_after__null_slist_container(void** state);
void test__slist_insert_after__non_inited_slist_container(void** state);
void test__slist_insert_after__invalid_pos(void** state);
void test__slist_insert_after__invalid_pos_end(void** state);
void test__slist_insert_after__empty_insert(void** state);
void test__slist_insert_after__n_insert_begin(void** state);
void test__slist_insert_after__n_insert_middle(void** state);
void test__slist_insert_after__n_insert_end(void** state);
void test__slist_insert_after__n_insert_end_multiple(void** state);
/*
 * test _slist_insert_after_n and _slist_insert_after_n_varg
 */
UT_CASE_DECLARATION(_slist_insert_after_n__slist_insert_after_n_varg)
void test__slist_insert_after_n__slist_insert_after_n_varg__null_slist_container(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__non_inited_slist_container(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos_end(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_0(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_begin(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_middle(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end(void** state);
void test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end_multiple(void** state);

#define UT_CSTL_SLIST_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_slist_private, test__create_slist__null_typename),\
    UT_CASE(test__create_slist__unregisted_type),\
    UT_CASE(test__create_slist__c_builtin_type),\
    UT_CASE(test__create_slist__libcstl_builtin_type),\
    UT_CASE(test__create_slist__user_defined_type),\
    UT_CASE(test__create_slist__user_defined_type_dup),\
    UT_CASE_BEGIN(_create_slist_auxiliary, test__create_slist_auxiliary__null_slist_container),\
    UT_CASE(test__create_slist_auxiliary__null_typename),\
    UT_CASE(test__create_slist_auxiliary__unregisted_type),\
    UT_CASE(test__create_slist_auxiliary__c_builtin),\
    UT_CASE(test__create_slist_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_slist_auxiliary__user_defined),\
    UT_CASE(test__create_slist_auxiliary__user_defined_dup),\
    UT_CASE_BEGIN(_slist_init_elem__slist_init_elem_varg,\
        test__slist_init_elem__slist_init_elem_varg__null_slist_container),\
    UT_CASE(test__slist_init_elem__slist_init_elem_varg__non_created_slist_container),\
    UT_CASE(test__slist_init_elem__slist_init_elem_varg__0_count),\
    UT_CASE(test__slist_init_elem__slist_init_elem_varg__count),\
    UT_CASE(test__slist_init_elem__slist_init_elem_varg__multiple_elem),\
    UT_CASE_BEGIN(_slist_destroy_auxiliary, test__slist_destroy_auxiliary__null_slist_container),\
    UT_CASE(test__slist_destroy_auxiliary__non_created_slist_container),\
    UT_CASE(test__slist_destroy_auxiliary__non_inited),\
    UT_CASE(test__slist_destroy_auxiliary__empty),\
    UT_CASE(test__slist_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_slist_assign_elem__slist_assign_elem_varg,\
        test__slist_assign_elem__slist_assign_elem_varg__null_slist_container),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__non_inited_slist_container),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__0_assign_0),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__0_assign_n),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__n_assign_0),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_greater_than_m),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_equal_to_m),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m),\
    UT_CASE(test__slist_assign_elem__slist_assign_elem_varg__n_assign_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_slist_push_front__slist_push_front_varg,\
        test__slist_push_front__slist_push_front_varg__null_slist_container),\
    UT_CASE(test__slist_push_front__slist_push_front_varg__non_inited_slist_container),\
    UT_CASE(test__slist_push_front__slist_push_front_varg__empty),\
    UT_CASE(test__slist_push_front__slist_push_front_varg__non_empty),\
    UT_CASE(test__slist_push_front__slist_push_front_varg__non_empty_multiple),\
    UT_CASE_BEGIN(_slist_resize_elem__slist_resize_elem_varg,\
        test__slist_resize_elem__slist_resize_elem_varg__null_slist_container),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__non_inited_slist_container),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__0_resize_0),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__0_resize_n),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__n_resize_0),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_greater_than_m),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_equal_to_m),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m),\
    UT_CASE(test__slist_resize_elem__slist_resize_elem_varg__n_resize_m_n_less_than_m_multiple),\
    UT_CASE_BEGIN(_slist_remove__slist_remove_varg, test__slist_remove__slist_remove_varg__null_slist_container),\
    UT_CASE(test__slist_remove__slist_remove_varg__non_inited_slist_container),\
    UT_CASE(test__slist_remove__slist_remove_varg__empty),\
    UT_CASE(test__slist_remove__slist_remove_varg__non_empty_no_removed),\
    UT_CASE(test__slist_remove__slist_remove_varg__non_empty_remove),\
    UT_CASE(test__slist_remove__slist_remove_varg__non_empty_remove_more),\
    UT_CASE(test__slist_remove__slist_remove_varg__non_empty_remove_more_multiple),\
    UT_CASE_BEGIN(_slist_init_elem_auxiliary, test__slist_init_elem_auxiliary__null_slist_container),\
    UT_CASE(test__slist_init_elem_auxiliary__null_elem),\
    UT_CASE(test__slist_init_elem_auxiliary__non_inited_slist),\
    UT_CASE(test__slist_init_elem_auxiliary__successfully_int),\
    UT_CASE(test__slist_init_elem_auxiliary__successfully_cstr),\
    UT_CASE(test__slist_init_elem_auxiliary__successfully_iterator),\
    UT_CASE(test__slist_init_elem_auxiliary__successfully_container),\
    UT_CASE(test__slist_init_elem_auxiliary__successfully_user_defined),\
    UT_CASE_BEGIN(_slist_insert, test__slist_insert__null_slist_container),\
    UT_CASE(test__slist_insert__non_inited_slist_container),\
    UT_CASE(test__slist_insert__invalid_pos),\
    UT_CASE(test__slist_insert__empty_insert),\
    UT_CASE(test__slist_insert__n_insert_begin),\
    UT_CASE(test__slist_insert__n_insert_middle),\
    UT_CASE(test__slist_insert__n_insert_end),\
    UT_CASE(test__slist_insert__n_insert_end_multiple),\
    UT_CASE_BEGIN(_slist_insert_n, test__slist_insert_n__null_slist_container),\
    UT_CASE(test__slist_insert_n__non_inited_slist_container),\
    UT_CASE(test__slist_insert_n__invalid_pos),\
    UT_CASE(test__slist_insert_n__0_insert_0),\
    UT_CASE(test__slist_insert_n__0_insert_n),\
    UT_CASE(test__slist_insert_n__n_insert_0),\
    UT_CASE(test__slist_insert_n__n_insert_begin),\
    UT_CASE(test__slist_insert_n__n_insert_middle),\
    UT_CASE(test__slist_insert_n__n_insert_end),\
    UT_CASE(test__slist_insert_n__n_insert_end_multiple),\
    UT_CASE_BEGIN(_slist_insert_after, test__slist_insert_after__null_slist_container),\
    UT_CASE(test__slist_insert_after__non_inited_slist_container),\
    UT_CASE(test__slist_insert_after__invalid_pos),\
    UT_CASE(test__slist_insert_after__invalid_pos_end),\
    UT_CASE(test__slist_insert_after__empty_insert),\
    UT_CASE(test__slist_insert_after__n_insert_begin),\
    UT_CASE(test__slist_insert_after__n_insert_middle),\
    UT_CASE(test__slist_insert_after__n_insert_end),\
    UT_CASE(test__slist_insert_after__n_insert_end_multiple),\
    UT_CASE_BEGIN(_slist_insert_after_n__slist_insert_after_n_varg,\
        test__slist_insert_after_n__slist_insert_after_n_varg__null_slist_container),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__non_inited_slist_container),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__invalid_pos_end),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_0),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_begin),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_middle),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end),\
    UT_CASE(test__slist_insert_after_n__slist_insert_after_n_varg__n_insert_end_multiple)

#endif /* _UT_CSTL_SLIST_PRIVATE_H_ */

