#ifndef _UT_CSTL_PAIR_H_
#define _UT_CSTL_PAIR_H_

UT_SUIT_DECLARATION(cstl_pair)
/*
 * test pair_init
 */
UT_CASE_DECLARATION(pair_init)
void test_pair_init__null_pair(void** state);
void test_pair_init__non_created(void** state);
void test_pair_init__init(void** state);
/*
 * test pair_init_copy
 */
UT_CASE_DECLARATION(pair_init_copy)
void test_pair_init_copy__null_dest(void** state);
void test_pair_init_copy__null_src(void** state);
void test_pair_init_copy__non_created_dest(void** state);
void test_pair_init_copy__non_inited_src(void** state);
void test_pair_init_copy__not_same_type(void** state);
void test_pair_init_copy__empty(void** state);
void test_pair_init_copy__non_empty(void** state);
/*
 * test pair_destroy
 */
UT_CASE_DECLARATION(pair_destroy)
void test_pair_destroy__null_pair(void** state);
void test_pair_destroy__non_created(void** state);
void test_pair_destroy__created(void** state);
void test_pair_destroy__inited(void** state);
/*
 * test pair_assign
 */
UT_CASE_DECLARATION(pair_assign)
void test_pair_assign__null_dest(void** state);
void test_pair_assign__null_src(void** state);
void test_pair_assign__non_init_dest(void** state);
void test_pair_assign__non_init_src(void** state);
void test_pair_assign__not_same_type(void** state);
void test_pair_assign__equal_not_same(void** state);
void test_pair_assign__same_pair(void** state);
void test_pair_assign__not_equal(void** state);
/*
 * test pair_first
 */
UT_CASE_DECLARATION(pair_first)
void test_pair_first__null_pair(void** state);
void test_pair_first__non_inited(void** state);
void test_pair_first__c_builtin(void** state);
void test_pair_first__str(void** state);
void test_pair_first__cstl_builtin(void** state);
void test_pair_first__user_define(void** state);
/*
 * test pair_second
 */
UT_CASE_DECLARATION(pair_second)
void test_pair_second__null_pair(void** state);
void test_pair_second__non_inited(void** state);
void test_pair_second__c_builtin(void** state);
void test_pair_second__str(void** state);
void test_pair_second__cstl_builtin(void** state);
void test_pair_second__user_define(void** state);
/*
 * test pair_equal
 */
UT_CASE_DECLARATION(pair_equal)
void test_pair_equal__null_first(void** state);
void test_pair_equal__null_second(void** state);
void test_pair_equal__non_inited_first(void** state);
void test_pair_equal__non_inited_second(void** state);
void test_pair_equal__not_same_type(void** state);
void test_pair_equal__same_pair(void** state);
void test_pair_equal__less_first_less(void** state);
void test_pair_equal__less_second_less(void** state);
void test_pair_equal__greater_first_greater(void** state);
void test_pair_equal__greater_second_greater(void** state);
void test_pair_equal__equal(void** state);
/*
 * test pair_not_equal
 */
UT_CASE_DECLARATION(pair_not_equal)
void test_pair_not_equal__null_first(void** state);
void test_pair_not_equal__null_second(void** state);
void test_pair_not_equal__non_inited_first(void** state);
void test_pair_not_equal__non_inited_second(void** state);
void test_pair_not_equal__not_same_type(void** state);
void test_pair_not_equal__same_pair(void** state);
void test_pair_not_equal__less_first_less(void** state);
void test_pair_not_equal__less_second_less(void** state);
void test_pair_not_equal__greater_first_greater(void** state);
void test_pair_not_equal__greater_second_greater(void** state);
void test_pair_not_equal__equal(void** state);
/*
 * test pair_less
 */
UT_CASE_DECLARATION(pair_less)
void test_pair_less__null_first(void** state);
void test_pair_less__null_second(void** state);
void test_pair_less__non_inited_first(void** state);
void test_pair_less__non_inited_second(void** state);
void test_pair_less__not_same_type(void** state);
void test_pair_less__same_pair(void** state);
void test_pair_less__less_first_less(void** state);
void test_pair_less__less_second_less(void** state);
void test_pair_less__greater_first_greater(void** state);
void test_pair_less__greater_second_greater(void** state);
void test_pair_less__equal(void** state);
/*
 * test pair_less_equal
 */
UT_CASE_DECLARATION(pair_less_equal)
void test_pair_less_equal__null_first(void** state);
void test_pair_less_equal__null_second(void** state);
void test_pair_less_equal__non_inited_first(void** state);
void test_pair_less_equal__non_inited_second(void** state);
void test_pair_less_equal__not_same_type(void** state);
void test_pair_less_equal__same_pair(void** state);
void test_pair_less_equal__less_first_less(void** state);
void test_pair_less_equal__less_second_less(void** state);
void test_pair_less_equal__greater_first_greater(void** state);
void test_pair_less_equal__greater_second_greater(void** state);
void test_pair_less_equal__equal(void** state);
/*
 * test pair_greater
 */
UT_CASE_DECLARATION(pair_greater)
void test_pair_greater__null_first(void** state);
void test_pair_greater__null_second(void** state);
void test_pair_greater__non_inited_first(void** state);
void test_pair_greater__non_inited_second(void** state);
void test_pair_greater__not_same_type(void** state);
void test_pair_greater__same_pair(void** state);
void test_pair_greater__less_first_less(void** state);
void test_pair_greater__less_second_less(void** state);
void test_pair_greater__greater_first_greater(void** state);
void test_pair_greater__greater_second_greater(void** state);
void test_pair_greater__equal(void** state);
/*
 * test pair_greater_equal
 */
UT_CASE_DECLARATION(pair_greater_equal)
void test_pair_greater_equal__null_first(void** state);
void test_pair_greater_equal__null_second(void** state);
void test_pair_greater_equal__non_inited_first(void** state);
void test_pair_greater_equal__non_inited_second(void** state);
void test_pair_greater_equal__not_same_type(void** state);
void test_pair_greater_equal__same_pair(void** state);
void test_pair_greater_equal__less_first_less(void** state);
void test_pair_greater_equal__less_second_less(void** state);
void test_pair_greater_equal__greater_first_greater(void** state);
void test_pair_greater_equal__greater_second_greater(void** state);
void test_pair_greater_equal__equal(void** state);

#define UT_CSTL_PAIR_CASE\
    UT_SUIT_BEGIN(cstl_pair, test_pair_init__null_pair),\
    UT_CASE(test_pair_init__non_created),\
    UT_CASE(test_pair_init__init),\
    UT_CASE_BEGIN(pair_init_copy, test_pair_init_copy__null_dest),\
    UT_CASE(test_pair_init_copy__null_src),\
    UT_CASE(test_pair_init_copy__non_created_dest),\
    UT_CASE(test_pair_init_copy__non_inited_src),\
    UT_CASE(test_pair_init_copy__not_same_type),\
    UT_CASE(test_pair_init_copy__empty),\
    UT_CASE(test_pair_init_copy__non_empty),\
    UT_CASE_BEGIN(pair_destroy, test_pair_destroy__null_pair),\
    UT_CASE(test_pair_destroy__non_created),\
    UT_CASE(test_pair_destroy__created),\
    UT_CASE(test_pair_destroy__inited),\
    UT_CASE_BEGIN(pair_assign, test_pair_assign__null_dest),\
    UT_CASE(test_pair_assign__null_src),\
    UT_CASE(test_pair_assign__non_init_dest),\
    UT_CASE(test_pair_assign__non_init_src),\
    UT_CASE(test_pair_assign__not_same_type),\
    UT_CASE(test_pair_assign__equal_not_same),\
    UT_CASE(test_pair_assign__same_pair),\
    UT_CASE(test_pair_assign__not_equal),\
    UT_CASE_BEGIN(pair_first, test_pair_first__null_pair),\
    UT_CASE(test_pair_first__non_inited),\
    UT_CASE(test_pair_first__c_builtin),\
    UT_CASE(test_pair_first__str),\
    UT_CASE(test_pair_first__cstl_builtin),\
    UT_CASE(test_pair_first__user_define),\
    UT_CASE_BEGIN(pair_second, test_pair_second__null_pair),\
    UT_CASE(test_pair_second__non_inited),\
    UT_CASE(test_pair_second__c_builtin),\
    UT_CASE(test_pair_second__str),\
    UT_CASE(test_pair_second__cstl_builtin),\
    UT_CASE(test_pair_second__user_define),\
    UT_CASE_BEGIN(pair_equal, test_pair_equal__null_first),\
    UT_CASE(test_pair_equal__null_second),\
    UT_CASE(test_pair_equal__non_inited_first),\
    UT_CASE(test_pair_equal__non_inited_second),\
    UT_CASE(test_pair_equal__not_same_type),\
    UT_CASE(test_pair_equal__same_pair),\
    UT_CASE(test_pair_equal__less_first_less),\
    UT_CASE(test_pair_equal__less_second_less),\
    UT_CASE(test_pair_equal__greater_first_greater),\
    UT_CASE(test_pair_equal__greater_second_greater),\
    UT_CASE(test_pair_equal__equal),\
    UT_CASE_BEGIN(pair_not_equal, test_pair_not_equal__null_first),\
    UT_CASE(test_pair_not_equal__null_second),\
    UT_CASE(test_pair_not_equal__non_inited_first),\
    UT_CASE(test_pair_not_equal__non_inited_second),\
    UT_CASE(test_pair_not_equal__not_same_type),\
    UT_CASE(test_pair_not_equal__same_pair),\
    UT_CASE(test_pair_not_equal__less_first_less),\
    UT_CASE(test_pair_not_equal__less_second_less),\
    UT_CASE(test_pair_not_equal__greater_first_greater),\
    UT_CASE(test_pair_not_equal__greater_second_greater),\
    UT_CASE(test_pair_not_equal__equal),\
    UT_CASE_BEGIN(pair_less, test_pair_less__null_first),\
    UT_CASE(test_pair_less__null_second),\
    UT_CASE(test_pair_less__non_inited_first),\
    UT_CASE(test_pair_less__non_inited_second),\
    UT_CASE(test_pair_less__not_same_type),\
    UT_CASE(test_pair_less__same_pair),\
    UT_CASE(test_pair_less__less_first_less),\
    UT_CASE(test_pair_less__less_second_less),\
    UT_CASE(test_pair_less__greater_first_greater),\
    UT_CASE(test_pair_less__greater_second_greater),\
    UT_CASE(test_pair_less__equal),\
    UT_CASE_BEGIN(pair_less_equal, test_pair_less_equal__null_first),\
    UT_CASE(test_pair_less_equal__null_second),\
    UT_CASE(test_pair_less_equal__non_inited_first),\
    UT_CASE(test_pair_less_equal__non_inited_second),\
    UT_CASE(test_pair_less_equal__not_same_type),\
    UT_CASE(test_pair_less_equal__same_pair),\
    UT_CASE(test_pair_less_equal__less_first_less),\
    UT_CASE(test_pair_less_equal__less_second_less),\
    UT_CASE(test_pair_less_equal__greater_first_greater),\
    UT_CASE(test_pair_less_equal__greater_second_greater),\
    UT_CASE(test_pair_less_equal__equal),\
    UT_CASE_BEGIN(pair_greater, test_pair_greater__null_first),\
    UT_CASE(test_pair_greater__null_second),\
    UT_CASE(test_pair_greater__non_inited_first),\
    UT_CASE(test_pair_greater__non_inited_second),\
    UT_CASE(test_pair_greater__not_same_type),\
    UT_CASE(test_pair_greater__same_pair),\
    UT_CASE(test_pair_greater__less_first_less),\
    UT_CASE(test_pair_greater__less_second_less),\
    UT_CASE(test_pair_greater__greater_first_greater),\
    UT_CASE(test_pair_greater__greater_second_greater),\
    UT_CASE(test_pair_greater__equal),\
    UT_CASE_BEGIN(pair_greater_equal, test_pair_greater_equal__null_first),\
    UT_CASE(test_pair_greater_equal__null_second),\
    UT_CASE(test_pair_greater_equal__non_inited_first),\
    UT_CASE(test_pair_greater_equal__non_inited_second),\
    UT_CASE(test_pair_greater_equal__not_same_type),\
    UT_CASE(test_pair_greater_equal__same_pair),\
    UT_CASE(test_pair_greater_equal__less_first_less),\
    UT_CASE(test_pair_greater_equal__less_second_less),\
    UT_CASE(test_pair_greater_equal__greater_first_greater),\
    UT_CASE(test_pair_greater_equal__greater_second_greater),\
    UT_CASE(test_pair_greater_equal__equal)

#endif /* _UT_CSTL_PAIR_H_ */

