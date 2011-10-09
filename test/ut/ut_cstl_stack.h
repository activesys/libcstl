#ifndef _UT_CSTL_STACK_H_
#define _UT_CSTL_STACK_H_

UT_SUIT_DECLARATION(cstl_stack)

/*
 * test stack_init
 */
UT_CASE_DECLARATION(stack_init)
void test_stack_init__null_stack_adaptor(void** state);
void test_stack_init__non_created_stack_adaptor(void** state);
void test_stack_init__successfully(void** state);
/*
 * test stack_init_copy
 */
UT_CASE_DECLARATION(stack_init_copy)
void test_stack_init_copy__null_dest_stack_adaptor(void** state);
void test_stack_init_copy__null_src_stack_adaptor(void** state);
void test_stack_init_copy__non_created_dest_stack_adaptor(void** state);
void test_stack_init_copy__non_inited_src_stack_adaptor(void** state);
void test_stack_init_copy__not_same_type(void** state);
void test_stack_init_copy__init_copy_empty(void** state);
void test_stack_init_copy__c_builtin(void** state);
void test_stack_init_copy__cstr(void** state);
void test_stack_init_copy__libcstl_builtin(void** state);
void test_stack_init_copy__user_define(void** state);
/*
 * test stack_destroy
 */
UT_CASE_DECLARATION(stack_destroy)
void test_stack_destroy__null_stack_adaptor(void** state);
void test_stack_destroy__non_created_stack_adaptor(void** state);
void test_stack_destroy__created_non_inited(void** state);
void test_stack_destroy__empty(void** state);
void test_stack_destroy__non_empty(void** state);
/*
 * test stack_size
 */
UT_CASE_DECLARATION(stack_size)
void test_stack_size__null_stack_adaptor(void** state);
void test_stack_size__non_inited_stack_adaptor(void** state);
void test_stack_size__empty(void** state);
void test_stack_size__non_empty(void** state);
/*
 * test stack_empty
 */
UT_CASE_DECLARATION(stack_empty)
void test_stack_empty__null_stack_adaptor(void** state);
void test_stack_empty__non_inited_stack_adaptor(void** state);
void test_stack_empty__empty(void** state);
void test_stack_empty__non_empty(void** state);
/*
 * test stack_equal
 */
UT_CASE_DECLARATION(stack_equal)
void test_stack_equal__null_first(void** state);
void test_stack_equal__null_second(void** state);
void test_stack_equal__non_inited_first(void** state);
void test_stack_equal__non_inited_second(void** state);
void test_stack_equal__not_same_type(void** state);
void test_stack_equal__same_stack(void** state);
void test_stack_equal__size_first_less_than_second(void** state);
void test_stack_equal__size_first_greater_than_second(void** state);
void test_stack_equal__size_equal_0(void** state);
void test_stack_equal__size_equal_elem_first_less_than_second(void** state);
void test_stack_equal__size_equal_elem_first_greater_than_second(void** state);
void test_stack_equal__size_equal_elem_equal(void** state);
/*
 * test stack_not_equal
 */
UT_CASE_DECLARATION(stack_not_equal)
void test_stack_not_equal__null_first(void** state);
void test_stack_not_equal__null_second(void** state);
void test_stack_not_equal__non_inited_first(void** state);
void test_stack_not_equal__non_inited_second(void** state);
void test_stack_not_equal__not_same_type(void** state);
void test_stack_not_equal__same_stack(void** state);
void test_stack_not_equal__size_first_less_than_second(void** state);
void test_stack_not_equal__size_first_greater_than_second(void** state);
void test_stack_not_equal__size_equal_0(void** state);
void test_stack_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_stack_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_stack_not_equal__size_equal_elem_equal(void** state);
/*
 * test stack_less
 */
UT_CASE_DECLARATION(stack_less)
void test_stack_less__null_first(void** state);
void test_stack_less__null_second(void** state);
void test_stack_less__non_inited_first(void** state);
void test_stack_less__non_inited_second(void** state);
void test_stack_less__not_same_type(void** state);
void test_stack_less__same_stack(void** state);
void test_stack_less__size_first_less_than_second(void** state);
void test_stack_less__size_first_greater_than_second(void** state);
void test_stack_less__size_equal_0(void** state);
void test_stack_less__size_equal_elem_first_less_than_second(void** state);
void test_stack_less__size_equal_elem_first_greater_than_second(void** state);
void test_stack_less__size_equal_elem_equal(void** state);
/*
 * test stack_less_equal
 */
UT_CASE_DECLARATION(stack_less_equal)
void test_stack_less_equal__null_first(void** state);
void test_stack_less_equal__null_second(void** state);
void test_stack_less_equal__non_inited_first(void** state);
void test_stack_less_equal__non_inited_second(void** state);
void test_stack_less_equal__not_same_type(void** state);
void test_stack_less_equal__same_stack(void** state);
void test_stack_less_equal__size_first_less_than_second(void** state);
void test_stack_less_equal__size_first_greater_than_second(void** state);
void test_stack_less_equal__size_equal_0(void** state);
void test_stack_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_stack_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_stack_less_equal__size_equal_elem_equal(void** state);
/*
 * test stack_greater
 */
UT_CASE_DECLARATION(stack_greater)
void test_stack_greater__null_first(void** state);
void test_stack_greater__null_second(void** state);
void test_stack_greater__non_inited_first(void** state);
void test_stack_greater__non_inited_second(void** state);
void test_stack_greater__not_same_type(void** state);
void test_stack_greater__same_stack(void** state);
void test_stack_greater__size_first_less_than_second(void** state);
void test_stack_greater__size_first_greater_than_second(void** state);
void test_stack_greater__size_equal_0(void** state);
void test_stack_greater__size_equal_elem_first_less_than_second(void** state);
void test_stack_greater__size_equal_elem_first_greater_than_second(void** state);
void test_stack_greater__size_equal_elem_equal(void** state);
/*
 * test stack_greater_equal
 */
UT_CASE_DECLARATION(stack_greater_equal)
void test_stack_greater_equal__null_first(void** state);
void test_stack_greater_equal__null_second(void** state);
void test_stack_greater_equal__non_inited_first(void** state);
void test_stack_greater_equal__non_inited_second(void** state);
void test_stack_greater_equal__not_same_type(void** state);
void test_stack_greater_equal__same_stack(void** state);
void test_stack_greater_equal__size_first_less_than_second(void** state);
void test_stack_greater_equal__size_first_greater_than_second(void** state);
void test_stack_greater_equal__size_equal_0(void** state);
void test_stack_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_stack_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_stack_greater_equal__size_equal_elem_equal(void** state);
/*
 * test stack_assign
 */
UT_CASE_DECLARATION(stack_assign)
void test_stack_assign__null_dest(void** state);
void test_stack_assign__null_src(void** state);
void test_stack_assign__non_inited_dest(void** state);
void test_stack_assign__non_inited_src(void** state);
void test_stack_assign__not_same_type(void** state);
void test_stack_assign__same_adaptor(void** state);
void test_stack_assign__0_assign_0(void** state);
void test_stack_assign__0_assign_n(void** state);
void test_stack_assign__n_assign_0(void** state);
void test_stack_assign__n_assign_n_stack_equal(void** state);
void test_stack_assign__n_assign_n_stack_not_equal(void** state);
void test_stack_assign__n_assign_m(void** state);
/*
 * test stack_pop
 */
UT_CASE_DECLARATION(stack_pop)
void test_stack_pop__null_stack_adaptor(void** state);
void test_stack_pop__non_inited_stack_adaptor(void** state);
void test_stack_pop__empty(void** state);
void test_stack_pop__successfully(void** state);
/*
 * test stack_top
 */
UT_CASE_DECLARATION(stack_top)
void test_stack_top__null_stack_adaptor(void** state);
void test_stack_top__non_inited_stack_adaptor(void** state);
void test_stack_top__empty(void** state);
void test_stack_top__successfully(void** state);

#define UT_CSTL_STACK_CASE\
    UT_SUIT_BEGIN(cstl_stack, test_stack_init__null_stack_adaptor),\
    UT_CASE(test_stack_init__non_created_stack_adaptor),\
    UT_CASE(test_stack_init__successfully),\
    UT_CASE_BEGIN(stack_init_copy, test_stack_init_copy__null_dest_stack_adaptor),\
    UT_CASE(test_stack_init_copy__null_src_stack_adaptor),\
    UT_CASE(test_stack_init_copy__non_created_dest_stack_adaptor),\
    UT_CASE(test_stack_init_copy__non_inited_src_stack_adaptor),\
    UT_CASE(test_stack_init_copy__not_same_type),\
    UT_CASE(test_stack_init_copy__init_copy_empty),\
    UT_CASE(test_stack_init_copy__c_builtin),\
    UT_CASE(test_stack_init_copy__cstr),\
    UT_CASE(test_stack_init_copy__libcstl_builtin),\
    UT_CASE(test_stack_init_copy__user_define),\
    UT_CASE_BEGIN(stack_destroy, test_stack_destroy__null_stack_adaptor),\
    UT_CASE(test_stack_destroy__non_created_stack_adaptor),\
    UT_CASE(test_stack_destroy__created_non_inited),\
    UT_CASE(test_stack_destroy__empty),\
    UT_CASE(test_stack_destroy__non_empty),\
    UT_CASE_BEGIN(stack_size, test_stack_size__null_stack_adaptor),\
    UT_CASE(test_stack_size__non_inited_stack_adaptor),\
    UT_CASE(test_stack_size__empty),\
    UT_CASE(test_stack_size__non_empty),\
    UT_CASE_BEGIN(stack_empty, test_stack_empty__null_stack_adaptor),\
    UT_CASE(test_stack_empty__non_inited_stack_adaptor),\
    UT_CASE(test_stack_empty__empty),\
    UT_CASE(test_stack_empty__non_empty),\
    UT_CASE_BEGIN(stack_equal, test_stack_equal__null_first),\
    UT_CASE(test_stack_equal__null_second),\
    UT_CASE(test_stack_equal__non_inited_first),\
    UT_CASE(test_stack_equal__non_inited_second),\
    UT_CASE(test_stack_equal__not_same_type),\
    UT_CASE(test_stack_equal__same_stack),\
    UT_CASE(test_stack_equal__size_first_less_than_second),\
    UT_CASE(test_stack_equal__size_first_greater_than_second),\
    UT_CASE(test_stack_equal__size_equal_0),\
    UT_CASE(test_stack_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_not_equal, test_stack_not_equal__null_first),\
    UT_CASE(test_stack_not_equal__null_second),\
    UT_CASE(test_stack_not_equal__non_inited_first),\
    UT_CASE(test_stack_not_equal__non_inited_second),\
    UT_CASE(test_stack_not_equal__not_same_type),\
    UT_CASE(test_stack_not_equal__same_stack),\
    UT_CASE(test_stack_not_equal__size_first_less_than_second),\
    UT_CASE(test_stack_not_equal__size_first_greater_than_second),\
    UT_CASE(test_stack_not_equal__size_equal_0),\
    UT_CASE(test_stack_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_less, test_stack_less__null_first),\
    UT_CASE(test_stack_less__null_second),\
    UT_CASE(test_stack_less__non_inited_first),\
    UT_CASE(test_stack_less__non_inited_second),\
    UT_CASE(test_stack_less__not_same_type),\
    UT_CASE(test_stack_less__same_stack),\
    UT_CASE(test_stack_less__size_first_less_than_second),\
    UT_CASE(test_stack_less__size_first_greater_than_second),\
    UT_CASE(test_stack_less__size_equal_0),\
    UT_CASE(test_stack_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_less_equal, test_stack_less_equal__null_first),\
    UT_CASE(test_stack_less_equal__null_second),\
    UT_CASE(test_stack_less_equal__non_inited_first),\
    UT_CASE(test_stack_less_equal__non_inited_second),\
    UT_CASE(test_stack_less_equal__not_same_type),\
    UT_CASE(test_stack_less_equal__same_stack),\
    UT_CASE(test_stack_less_equal__size_first_less_than_second),\
    UT_CASE(test_stack_less_equal__size_first_greater_than_second),\
    UT_CASE(test_stack_less_equal__size_equal_0),\
    UT_CASE(test_stack_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_greater, test_stack_greater__null_first),\
    UT_CASE(test_stack_greater__null_second),\
    UT_CASE(test_stack_greater__non_inited_first),\
    UT_CASE(test_stack_greater__non_inited_second),\
    UT_CASE(test_stack_greater__not_same_type),\
    UT_CASE(test_stack_greater__same_stack),\
    UT_CASE(test_stack_greater__size_first_less_than_second),\
    UT_CASE(test_stack_greater__size_first_greater_than_second),\
    UT_CASE(test_stack_greater__size_equal_0),\
    UT_CASE(test_stack_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_greater_equal, test_stack_greater_equal__null_first),\
    UT_CASE(test_stack_greater_equal__null_second),\
    UT_CASE(test_stack_greater_equal__non_inited_first),\
    UT_CASE(test_stack_greater_equal__non_inited_second),\
    UT_CASE(test_stack_greater_equal__not_same_type),\
    UT_CASE(test_stack_greater_equal__same_stack),\
    UT_CASE(test_stack_greater_equal__size_first_less_than_second),\
    UT_CASE(test_stack_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_stack_greater_equal__size_equal_0),\
    UT_CASE(test_stack_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_stack_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_stack_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(stack_assign, test_stack_assign__null_dest),\
    UT_CASE(test_stack_assign__null_src),\
    UT_CASE(test_stack_assign__non_inited_dest),\
    UT_CASE(test_stack_assign__non_inited_src),\
    UT_CASE(test_stack_assign__not_same_type),\
    UT_CASE(test_stack_assign__same_adaptor),\
    UT_CASE(test_stack_assign__0_assign_0),\
    UT_CASE(test_stack_assign__0_assign_n),\
    UT_CASE(test_stack_assign__n_assign_0),\
    UT_CASE(test_stack_assign__n_assign_n_stack_equal),\
    UT_CASE(test_stack_assign__n_assign_n_stack_not_equal),\
    UT_CASE(test_stack_assign__n_assign_m),\
    UT_CASE_BEGIN(stack_pop, test_stack_pop__null_stack_adaptor),\
    UT_CASE(test_stack_pop__non_inited_stack_adaptor),\
    UT_CASE(test_stack_pop__empty),\
    UT_CASE(test_stack_pop__successfully),\
    UT_CASE_BEGIN(stack_top, test_stack_top__null_stack_adaptor),\
    UT_CASE(test_stack_top__non_inited_stack_adaptor),\
    UT_CASE(test_stack_top__empty),\
    UT_CASE(test_stack_top__successfully)

#endif /* _UT_CSTL_STACK_H_ */

