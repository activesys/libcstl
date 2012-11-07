#ifndef _UT_CSTL_NUMERIC_PRIVATE_H_
#define _UT_CSTL_NUMERIC_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_numeric_private)

/*
 * test _algo_iota
 */
UT_CASE_DECLARATION(_algo_iota)
void test__algo_iota__invalid_range(void** state);
void test__algo_iota__invalid_range2(void** state);
void test__algo_iota__invalid_range3(void** state);
void test__algo_iota__empty(void** state);
void test__algo_iota__not_empty(void** state);
/*
 * test _algo_accumulate
 */
UT_CASE_DECLARATION(_algo_accumulate)
void test__algo_accumulate__invalid_range(void** state);
void test__algo_accumulate__invalid_range2(void** state);
void test__algo_accumulate__invalid_range3(void** state);
void test__algo_accumulate__output_NULL(void** state);
void test__algo_accumulate__empty(void** state);
void test__algo_accumulate__not_empty(void** state);
/*
 * test _algo_accumulate_if
 */
UT_CASE_DECLARATION(_algo_accumulate_if)
void test__algo_accumulate_if__invalid_range(void** state);
void test__algo_accumulate_if__invalid_range2(void** state);
void test__algo_accumulate_if__invalid_range3(void** state);
void test__algo_accumulate_if__output_NULL(void** state);
void test__algo_accumulate_if__empty(void** state);
void test__algo_accumulate_if__bfun_NULL_not_empty(void** state);
void test__algo_accumulate_if__not_empty(void** state);
/*
 * test _algo_inner_product
 */
UT_CASE_DECLARATION(_algo_inner_product)
void test__algo_inner_product__invalid_first_range(void** state);
void test__algo_inner_product__invalid_second_range(void** state);
void test__algo_inner_product__not_same_type(void** state);
void test__algo_inner_product__output_NULL(void** state);
void test__algo_inner_product__empty(void** state);
void test__algo_inner_product__not_empty(void** state);
/*
 * test _algo_inner_product_if
 */
UT_CASE_DECLARATION(_algo_inner_product_if)
void test__algo_inner_product_if__invalid_first_range(void** state);
void test__algo_inner_product_if__invalid_second_range(void** state);
void test__algo_inner_product_if__not_same_type(void** state);
void test__algo_inner_product_if__output_NULL(void** state);
void test__algo_inner_product_if__empty(void** state);
void test__algo_inner_product_if__bfun_op1_NULL_not_empty(void** state);
void test__algo_inner_product_if__bfun_op2_NULL_not_empty(void** state);
void test__algo_inner_product_if__not_empty(void** state);

#define UT_CSTL_NUMERIC_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_numeric_private, test__algo_iota__invalid_range),\
    UT_CASE(test__algo_iota__invalid_range2),\
    UT_CASE(test__algo_iota__invalid_range3),\
    UT_CASE(test__algo_iota__empty),\
    UT_CASE(test__algo_iota__not_empty),\
    UT_CASE_BEGIN(_algo_accumulate, test__algo_accumulate__invalid_range),\
    UT_CASE(test__algo_accumulate__invalid_range2),\
    UT_CASE(test__algo_accumulate__invalid_range3),\
    UT_CASE(test__algo_accumulate__output_NULL),\
    UT_CASE(test__algo_accumulate__empty),\
    UT_CASE(test__algo_accumulate__not_empty),\
    UT_CASE_BEGIN(_algo_accumulate_if, test__algo_accumulate_if__invalid_range),\
    UT_CASE(test__algo_accumulate_if__invalid_range2),\
    UT_CASE(test__algo_accumulate_if__invalid_range3),\
    UT_CASE(test__algo_accumulate_if__output_NULL),\
    UT_CASE(test__algo_accumulate_if__empty),\
    UT_CASE(test__algo_accumulate_if__bfun_NULL_not_empty),\
    UT_CASE(test__algo_accumulate_if__not_empty),\
    UT_CASE_BEGIN(_algo_inner_product, test__algo_inner_product__invalid_first_range),\
    UT_CASE(test__algo_inner_product__invalid_second_range),\
    UT_CASE(test__algo_inner_product__not_same_type),\
    UT_CASE(test__algo_inner_product__output_NULL),\
    UT_CASE(test__algo_inner_product__empty),\
    UT_CASE(test__algo_inner_product__not_empty),\
    UT_CASE_BEGIN(_algo_inner_product_if, test__algo_inner_product_if__invalid_first_range),\
    UT_CASE(test__algo_inner_product_if__invalid_second_range),\
    UT_CASE(test__algo_inner_product_if__not_same_type),\
    UT_CASE(test__algo_inner_product_if__output_NULL),\
    UT_CASE(test__algo_inner_product_if__empty),\
    UT_CASE(test__algo_inner_product_if__bfun_op1_NULL_not_empty),\
    UT_CASE(test__algo_inner_product_if__bfun_op2_NULL_not_empty),\
    UT_CASE(test__algo_inner_product_if__not_empty)

#endif /* _UT_CSTL_NUMERIC_PRIVATE_H_ */

