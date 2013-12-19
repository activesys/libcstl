#ifndef _UT_CSTL_FUNCTION_H_
#define _UT_CSTL_FUNCTION_H_

UT_SUIT_DECLARATION(cstl_function)

/*
 * test fun_equal_pointer usage
 */
UT_CASE_DECLARATION(fun_equal_pointer_usage)
void test__fun_equal_pointer_usage__algo_unique_copy(void** state);
/*
 * test fun_not_equal_pointer usage
 */
UT_CASE_DECLARATION(fun_not_equal_pointer_usage)
void test__fun_not_equal_pointer_usage__algo_unique_copy_if(void** state);
/*
 * test fun_greater_pointer usage
 */
UT_CASE_DECLARATION(fun_greater_pointer_usage)
void test__fun_greater_pointer_usage__algo_sort_if(void** state);
/*
 * test fun_greater_equal_pointer usage
 */
UT_CASE_DECLARATION(fun_greater_equal_pointer_usage)
void test__fun_greater_equal_pointer_usage__algo_sort_if(void** state);
/*
 * test fun_less_pointer usage
 */
UT_CASE_DECLARATION(fun_less_pointer_usage)
void test__fun_less_pointer_usage__algo_sort_if(void** state);
/*
 * test fun_less_equal_pointer usage
 */
UT_CASE_DECLARATION(fun_less_equal_pointer_usage)
void test__fun_less_equal_pointer_usage__algo_sort_if(void** state);

#define UT_CASE_FUNCTION_CASE\
    UT_SUIT_BEGIN(cstl_function, test__fun_equal_pointer_usage__algo_unique_copy),\
    UT_CASE_BEGIN(fun_not_equal_pointer_usage, test__fun_not_equal_pointer_usage__algo_unique_copy_if),\
    UT_CASE_BEGIN(fun_greater_pointer_usage, test__fun_greater_pointer_usage__algo_sort_if),\
    UT_CASE_BEGIN(fun_greater_equal_pointer_usage, test__fun_greater_equal_pointer_usage__algo_sort_if),\
    UT_CASE_BEGIN(fun_less_pointer_usage, test__fun_less_pointer_usage__algo_sort_if),\
    UT_CASE_BEGIN(fun_less_equal_pointer_usage, test__fun_less_equal_pointer_usage__algo_sort_if)

#endif /* _UT_CSTL_FUNCTION_H_ */

