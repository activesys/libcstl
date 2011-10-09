#ifndef _UT_CSTL_QUEUE_H_
#define _UT_CSTL_QUEUE_H_

UT_SUIT_DECLARATION(cstl_queue)

/*
 * test queue_init
 */
UT_CASE_DECLARATION(queue_init)
void test_queue_init__null_queue_adaptor(void** state);
void test_queue_init__non_created_queue_adaptor(void** state);
void test_queue_init__successfully(void** state);
/*
 * test queue_init_copy
 */
UT_CASE_DECLARATION(queue_init_copy)
void test_queue_init_copy__null_dest_queue_adaptor(void** state);
void test_queue_init_copy__null_src_queue_adaptor(void** state);
void test_queue_init_copy__non_created_dest_queue_adaptor(void** state);
void test_queue_init_copy__non_inited_src_queue_adaptor(void** state);
void test_queue_init_copy__not_same_type(void** state);
void test_queue_init_copy__init_copy_empty(void** state);
void test_queue_init_copy__c_builtin(void** state);
void test_queue_init_copy__cstr(void** state);
void test_queue_init_copy__libcstl_builtin(void** state);
void test_queue_init_copy__user_define(void** state);
/*
 * test queue_destroy
 */
UT_CASE_DECLARATION(queue_destroy)
void test_queue_destroy__null_queue_adaptor(void** state);
void test_queue_destroy__non_created_queue_adaptor(void** state);
void test_queue_destroy__created_non_inited(void** state);
void test_queue_destroy__empty(void** state);
void test_queue_destroy__non_empty(void** state);
/*
 * test queue_size
 */
UT_CASE_DECLARATION(queue_size)
void test_queue_size__null_queue_adaptor(void** state);
void test_queue_size__non_inited_queue_adaptor(void** state);
void test_queue_size__empty(void** state);
void test_queue_size__non_empty(void** state);
/*
 * test queue_empty
 */
UT_CASE_DECLARATION(queue_empty)
void test_queue_empty__null_queue_adaptor(void** state);
void test_queue_empty__non_inited_queue_adaptor(void** state);
void test_queue_empty__empty(void** state);
void test_queue_empty__non_empty(void** state);
/*
 * test queue_equal
 */
UT_CASE_DECLARATION(queue_equal)
void test_queue_equal__null_first(void** state);
void test_queue_equal__null_second(void** state);
void test_queue_equal__non_inited_first(void** state);
void test_queue_equal__non_inited_second(void** state);
void test_queue_equal__not_same_type(void** state);
void test_queue_equal__same_queue(void** state);
void test_queue_equal__size_first_less_than_second(void** state);
void test_queue_equal__size_first_greater_than_second(void** state);
void test_queue_equal__size_equal_0(void** state);
void test_queue_equal__size_equal_elem_first_less_than_second(void** state);
void test_queue_equal__size_equal_elem_first_greater_than_second(void** state);
void test_queue_equal__size_equal_elem_equal(void** state);
/*
 * test queue_not_equal
 */
UT_CASE_DECLARATION(queue_not_equal)
void test_queue_not_equal__null_first(void** state);
void test_queue_not_equal__null_second(void** state);
void test_queue_not_equal__non_inited_first(void** state);
void test_queue_not_equal__non_inited_second(void** state);
void test_queue_not_equal__not_same_type(void** state);
void test_queue_not_equal__same_queue(void** state);
void test_queue_not_equal__size_first_less_than_second(void** state);
void test_queue_not_equal__size_first_greater_than_second(void** state);
void test_queue_not_equal__size_equal_0(void** state);
void test_queue_not_equal__size_equal_elem_first_less_than_second(void** state);
void test_queue_not_equal__size_equal_elem_first_greater_than_second(void** state);
void test_queue_not_equal__size_equal_elem_equal(void** state);
/*
 * test queue_less
 */
UT_CASE_DECLARATION(queue_less)
void test_queue_less__null_first(void** state);
void test_queue_less__null_second(void** state);
void test_queue_less__non_inited_first(void** state);
void test_queue_less__non_inited_second(void** state);
void test_queue_less__not_same_type(void** state);
void test_queue_less__same_queue(void** state);
void test_queue_less__size_first_less_than_second(void** state);
void test_queue_less__size_first_greater_than_second(void** state);
void test_queue_less__size_equal_0(void** state);
void test_queue_less__size_equal_elem_first_less_than_second(void** state);
void test_queue_less__size_equal_elem_first_greater_than_second(void** state);
void test_queue_less__size_equal_elem_equal(void** state);
/*
 * test queue_less_equal
 */
UT_CASE_DECLARATION(queue_less_equal)
void test_queue_less_equal__null_first(void** state);
void test_queue_less_equal__null_second(void** state);
void test_queue_less_equal__non_inited_first(void** state);
void test_queue_less_equal__non_inited_second(void** state);
void test_queue_less_equal__not_same_type(void** state);
void test_queue_less_equal__same_queue(void** state);
void test_queue_less_equal__size_first_less_than_second(void** state);
void test_queue_less_equal__size_first_greater_than_second(void** state);
void test_queue_less_equal__size_equal_0(void** state);
void test_queue_less_equal__size_equal_elem_first_less_than_second(void** state);
void test_queue_less_equal__size_equal_elem_first_greater_than_second(void** state);
void test_queue_less_equal__size_equal_elem_equal(void** state);
/*
 * test queue_greater
 */
UT_CASE_DECLARATION(queue_greater)
void test_queue_greater__null_first(void** state);
void test_queue_greater__null_second(void** state);
void test_queue_greater__non_inited_first(void** state);
void test_queue_greater__non_inited_second(void** state);
void test_queue_greater__not_same_type(void** state);
void test_queue_greater__same_queue(void** state);
void test_queue_greater__size_first_less_than_second(void** state);
void test_queue_greater__size_first_greater_than_second(void** state);
void test_queue_greater__size_equal_0(void** state);
void test_queue_greater__size_equal_elem_first_less_than_second(void** state);
void test_queue_greater__size_equal_elem_first_greater_than_second(void** state);
void test_queue_greater__size_equal_elem_equal(void** state);
/*
 * test queue_greater_equal
 */
UT_CASE_DECLARATION(queue_greater_equal)
void test_queue_greater_equal__null_first(void** state);
void test_queue_greater_equal__null_second(void** state);
void test_queue_greater_equal__non_inited_first(void** state);
void test_queue_greater_equal__non_inited_second(void** state);
void test_queue_greater_equal__not_same_type(void** state);
void test_queue_greater_equal__same_queue(void** state);
void test_queue_greater_equal__size_first_less_than_second(void** state);
void test_queue_greater_equal__size_first_greater_than_second(void** state);
void test_queue_greater_equal__size_equal_0(void** state);
void test_queue_greater_equal__size_equal_elem_first_less_than_second(void** state);
void test_queue_greater_equal__size_equal_elem_first_greater_than_second(void** state);
void test_queue_greater_equal__size_equal_elem_equal(void** state);
/*
 * test queue_assign
 */
UT_CASE_DECLARATION(queue_assign)
void test_queue_assign__null_dest(void** state);
void test_queue_assign__null_src(void** state);
void test_queue_assign__non_inited_dest(void** state);
void test_queue_assign__non_inited_src(void** state);
void test_queue_assign__not_same_type(void** state);
void test_queue_assign__same_adaptor(void** state);
void test_queue_assign__0_assign_0(void** state);
void test_queue_assign__0_assign_n(void** state);
void test_queue_assign__n_assign_0(void** state);
void test_queue_assign__n_assign_n_queue_equal(void** state);
void test_queue_assign__n_assign_n_queue_not_equal(void** state);
void test_queue_assign__n_assign_m(void** state);
/*
 * test queue_pop
 */
UT_CASE_DECLARATION(queue_pop)
void test_queue_pop__null_queue_adaptor(void** state);
void test_queue_pop__non_inited_queue_adaptor(void** state);
void test_queue_pop__empty(void** state);
void test_queue_pop__successfully(void** state);
/*
 * test queue_front
 */
UT_CASE_DECLARATION(queue_front)
void test_queue_front__null_queue_adaptor(void** state);
void test_queue_front__non_inited_queue_adaptor(void** state);
void test_queue_front__empty(void** state);
void test_queue_front__successfully(void** state);
/*
 * test queue_back
 */
UT_CASE_DECLARATION(queue_back)
void test_queue_back__null_queue_adaptor(void** state);
void test_queue_back__non_inited_queue_adaptor(void** state);
void test_queue_back__empty(void** state);
void test_queue_back__successfully(void** state);

#define UT_CSTL_QUEUE_CASE\
    UT_SUIT_BEGIN(cstl_queue, test_queue_init__null_queue_adaptor),\
    UT_CASE(test_queue_init__non_created_queue_adaptor),\
    UT_CASE(test_queue_init__successfully),\
    UT_CASE_BEGIN(queue_init_copy, test_queue_init_copy__null_dest_queue_adaptor),\
    UT_CASE(test_queue_init_copy__null_src_queue_adaptor),\
    UT_CASE(test_queue_init_copy__non_created_dest_queue_adaptor),\
    UT_CASE(test_queue_init_copy__non_inited_src_queue_adaptor),\
    UT_CASE(test_queue_init_copy__not_same_type),\
    UT_CASE(test_queue_init_copy__init_copy_empty),\
    UT_CASE(test_queue_init_copy__c_builtin),\
    UT_CASE(test_queue_init_copy__cstr),\
    UT_CASE(test_queue_init_copy__libcstl_builtin),\
    UT_CASE(test_queue_init_copy__user_define),\
    UT_CASE_BEGIN(queue_destroy, test_queue_destroy__null_queue_adaptor),\
    UT_CASE(test_queue_destroy__non_created_queue_adaptor),\
    UT_CASE(test_queue_destroy__created_non_inited),\
    UT_CASE(test_queue_destroy__empty),\
    UT_CASE(test_queue_destroy__non_empty),\
    UT_CASE_BEGIN(queue_size, test_queue_size__null_queue_adaptor),\
    UT_CASE(test_queue_size__non_inited_queue_adaptor),\
    UT_CASE(test_queue_size__empty),\
    UT_CASE(test_queue_size__non_empty),\
    UT_CASE_BEGIN(queue_empty, test_queue_empty__null_queue_adaptor),\
    UT_CASE(test_queue_empty__non_inited_queue_adaptor),\
    UT_CASE(test_queue_empty__empty),\
    UT_CASE(test_queue_empty__non_empty),\
    UT_CASE_BEGIN(queue_equal, test_queue_equal__null_first),\
    UT_CASE(test_queue_equal__null_second),\
    UT_CASE(test_queue_equal__non_inited_first),\
    UT_CASE(test_queue_equal__non_inited_second),\
    UT_CASE(test_queue_equal__not_same_type),\
    UT_CASE(test_queue_equal__same_queue),\
    UT_CASE(test_queue_equal__size_first_less_than_second),\
    UT_CASE(test_queue_equal__size_first_greater_than_second),\
    UT_CASE(test_queue_equal__size_equal_0),\
    UT_CASE(test_queue_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_not_equal, test_queue_not_equal__null_first),\
    UT_CASE(test_queue_not_equal__null_second),\
    UT_CASE(test_queue_not_equal__non_inited_first),\
    UT_CASE(test_queue_not_equal__non_inited_second),\
    UT_CASE(test_queue_not_equal__not_same_type),\
    UT_CASE(test_queue_not_equal__same_queue),\
    UT_CASE(test_queue_not_equal__size_first_less_than_second),\
    UT_CASE(test_queue_not_equal__size_first_greater_than_second),\
    UT_CASE(test_queue_not_equal__size_equal_0),\
    UT_CASE(test_queue_not_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_not_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_not_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_less, test_queue_less__null_first),\
    UT_CASE(test_queue_less__null_second),\
    UT_CASE(test_queue_less__non_inited_first),\
    UT_CASE(test_queue_less__non_inited_second),\
    UT_CASE(test_queue_less__not_same_type),\
    UT_CASE(test_queue_less__same_queue),\
    UT_CASE(test_queue_less__size_first_less_than_second),\
    UT_CASE(test_queue_less__size_first_greater_than_second),\
    UT_CASE(test_queue_less__size_equal_0),\
    UT_CASE(test_queue_less__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_less__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_less__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_less_equal, test_queue_less_equal__null_first),\
    UT_CASE(test_queue_less_equal__null_second),\
    UT_CASE(test_queue_less_equal__non_inited_first),\
    UT_CASE(test_queue_less_equal__non_inited_second),\
    UT_CASE(test_queue_less_equal__not_same_type),\
    UT_CASE(test_queue_less_equal__same_queue),\
    UT_CASE(test_queue_less_equal__size_first_less_than_second),\
    UT_CASE(test_queue_less_equal__size_first_greater_than_second),\
    UT_CASE(test_queue_less_equal__size_equal_0),\
    UT_CASE(test_queue_less_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_less_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_less_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_greater, test_queue_greater__null_first),\
    UT_CASE(test_queue_greater__null_second),\
    UT_CASE(test_queue_greater__non_inited_first),\
    UT_CASE(test_queue_greater__non_inited_second),\
    UT_CASE(test_queue_greater__not_same_type),\
    UT_CASE(test_queue_greater__same_queue),\
    UT_CASE(test_queue_greater__size_first_less_than_second),\
    UT_CASE(test_queue_greater__size_first_greater_than_second),\
    UT_CASE(test_queue_greater__size_equal_0),\
    UT_CASE(test_queue_greater__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_greater__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_greater__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_greater_equal, test_queue_greater_equal__null_first),\
    UT_CASE(test_queue_greater_equal__null_second),\
    UT_CASE(test_queue_greater_equal__non_inited_first),\
    UT_CASE(test_queue_greater_equal__non_inited_second),\
    UT_CASE(test_queue_greater_equal__not_same_type),\
    UT_CASE(test_queue_greater_equal__same_queue),\
    UT_CASE(test_queue_greater_equal__size_first_less_than_second),\
    UT_CASE(test_queue_greater_equal__size_first_greater_than_second),\
    UT_CASE(test_queue_greater_equal__size_equal_0),\
    UT_CASE(test_queue_greater_equal__size_equal_elem_first_less_than_second),\
    UT_CASE(test_queue_greater_equal__size_equal_elem_first_greater_than_second),\
    UT_CASE(test_queue_greater_equal__size_equal_elem_equal),\
    UT_CASE_BEGIN(queue_assign, test_queue_assign__null_dest),\
    UT_CASE(test_queue_assign__null_src),\
    UT_CASE(test_queue_assign__non_inited_dest),\
    UT_CASE(test_queue_assign__non_inited_src),\
    UT_CASE(test_queue_assign__not_same_type),\
    UT_CASE(test_queue_assign__same_adaptor),\
    UT_CASE(test_queue_assign__0_assign_0),\
    UT_CASE(test_queue_assign__0_assign_n),\
    UT_CASE(test_queue_assign__n_assign_0),\
    UT_CASE(test_queue_assign__n_assign_n_queue_equal),\
    UT_CASE(test_queue_assign__n_assign_n_queue_not_equal),\
    UT_CASE(test_queue_assign__n_assign_m),\
    UT_CASE_BEGIN(queue_pop, test_queue_pop__null_queue_adaptor),\
    UT_CASE(test_queue_pop__non_inited_queue_adaptor),\
    UT_CASE(test_queue_pop__empty),\
    UT_CASE(test_queue_pop__successfully),\
    UT_CASE_BEGIN(queue_front, test_queue_front__null_queue_adaptor),\
    UT_CASE(test_queue_front__non_inited_queue_adaptor),\
    UT_CASE(test_queue_front__empty),\
    UT_CASE(test_queue_front__successfully),\
    UT_CASE_BEGIN(queue_back, test_queue_back__null_queue_adaptor),\
    UT_CASE(test_queue_back__non_inited_queue_adaptor),\
    UT_CASE(test_queue_back__empty),\
    UT_CASE(test_queue_back__successfully)

#endif /* _UT_CSTL_QUEUE_H_ */

