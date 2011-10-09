#ifndef _UT_CSTL_PAIR_AUX_H_
#define _UT_CSTL_PAIR_AUX_H_

UT_SUIT_DECLARATION(cstl_pair_aux)

/*
 * test _pair_same_type
 */
UT_CASE_DECLARATION(_pair_same_type)
void test__pair_same_type__first_null(void** state);
void test__pair_same_type__second_null(void** state);
void test__pair_same_type__same_pair(void** state);
void test__pair_same_type__first_noninited(void** state);
void test__pair_same_type__second_noninited(void** state);
void test__pair_same_type__not_same_first_type(void** state);
void test__pair_same_type__not_same_second_type(void** state);
void test__pair_same_type__same_type(void** state);

#define UT_CSTL_PAIR_AUX_CASE\
    UT_SUIT_BEGIN(cstl_pair_aux, test__pair_same_type__first_null),\
    UT_CASE(test__pair_same_type__second_null),\
    UT_CASE(test__pair_same_type__same_pair),\
    UT_CASE(test__pair_same_type__first_noninited),\
    UT_CASE(test__pair_same_type__second_noninited),\
    UT_CASE(test__pair_same_type__not_same_first_type),\
    UT_CASE(test__pair_same_type__not_same_second_type),\
    UT_CASE(test__pair_same_type__same_type)

#endif /* _UT_CSTL_PAIR_AUX_H_ */

