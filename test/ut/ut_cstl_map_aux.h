#ifndef _UT_CSTL_MAP_AUX_H_
#define _UT_CSTL_MAP_AUX_H_

UT_SUIT_DECLARATION(cstl_map_aux)
/*
 * test _map_same_pair_type_ex
 */
UT_CASE_DECLARATION(_map_same_pair_type_ex)
void test__map_same_pair_type_ex__first_null(void** state);
void test__map_same_pair_type_ex__second_null(void** state);
void test__map_same_pair_type_ex__same_pair(void** state);
void test__map_same_pair_type_ex__first_noninited(void** state);
void test__map_same_pair_type_ex__second_noninited(void** state);
void test__map_same_pair_type_ex__not_same_first_type(void** state);
void test__map_same_pair_type_ex__not_same_second_type(void** state);
void test__map_same_pair_type_ex__not_mapkeycompare(void** state);
void test__map_same_pair_type_ex__not_mapvaluecompare(void** state);
void test__map_same_pair_type_ex__same_type(void** state);
/*
 * test _map_same_pair_type
 */
UT_CASE_DECLARATION(_map_same_pair_type)
void test__map_same_pair_type__first_null(void** state);
void test__map_same_pair_type__second_null(void** state);
void test__map_same_pair_type__same_pair(void** state);
void test__map_same_pair_type__first_noninited(void** state);
void test__map_same_pair_type__second_noninited(void** state);
void test__map_same_pair_type__not_same_first_type(void** state);
void test__map_same_pair_type__not_same_second_type(void** state);
void test__map_same_pair_type__not_mapkeycompare(void** state);
void test__map_same_pair_type__not_mapvaluecompare(void** state);
void test__map_same_pair_type__same_type(void** state);
/*
 * test _map_value_compare
 */
UT_CASE_DECLARATION(_map_value_compare)
void test__map_value_compare__null_first(void** state);
void test__map_value_compare__null_second(void** state);
void test__map_value_compare__null_output(void** state);
void test__map_value_compare__noninited_first(void** state);
void test__map_value_compare__noninited_second(void** state);
void test__map_value_compare__not_same(void** state);
void test__map_value_compare__no_mapkeycompare_result_true(void** state);
void test__map_value_compare__no_mapkeycompare_result_false(void** state);
void test__map_value_compare__user_mapkeycompare_result_true(void** state);
void test__map_value_compare__user_mapkeycompare_result_false(void** state);

#define UT_CSTL_MAP_AUX_CASE\
    UT_SUIT_BEGIN(cstl_map_aux, test__map_same_pair_type_ex__first_null),\
    UT_CASE(test__map_same_pair_type_ex__second_null),\
    UT_CASE(test__map_same_pair_type_ex__same_pair),\
    UT_CASE(test__map_same_pair_type_ex__first_noninited),\
    UT_CASE(test__map_same_pair_type_ex__second_noninited),\
    UT_CASE(test__map_same_pair_type_ex__not_same_first_type),\
    UT_CASE(test__map_same_pair_type_ex__not_same_second_type),\
    UT_CASE(test__map_same_pair_type_ex__not_mapkeycompare),\
    UT_CASE(test__map_same_pair_type_ex__not_mapvaluecompare),\
    UT_CASE(test__map_same_pair_type_ex__same_type),\
    UT_CASE_BEGIN(_map_same_pair_type, test__map_same_pair_type__first_null),\
    UT_CASE(test__map_same_pair_type__second_null),\
    UT_CASE(test__map_same_pair_type__same_pair),\
    UT_CASE(test__map_same_pair_type__first_noninited),\
    UT_CASE(test__map_same_pair_type__second_noninited),\
    UT_CASE(test__map_same_pair_type__not_same_first_type),\
    UT_CASE(test__map_same_pair_type__not_same_second_type),\
    UT_CASE(test__map_same_pair_type__not_mapkeycompare),\
    UT_CASE(test__map_same_pair_type__not_mapvaluecompare),\
    UT_CASE(test__map_same_pair_type__same_type),\
    UT_CASE_BEGIN(_map_value_compare, test__map_value_compare__null_first),\
    UT_CASE(test__map_value_compare__null_second),\
    UT_CASE(test__map_value_compare__null_output),\
    UT_CASE(test__map_value_compare__noninited_first),\
    UT_CASE(test__map_value_compare__noninited_second),\
    UT_CASE(test__map_value_compare__not_same),\
    UT_CASE(test__map_value_compare__no_mapkeycompare_result_true),\
    UT_CASE(test__map_value_compare__no_mapkeycompare_result_false),\
    UT_CASE(test__map_value_compare__user_mapkeycompare_result_true),\
    UT_CASE(test__map_value_compare__user_mapkeycompare_result_false)

#endif /* _UT_CSTL_MAP_AUX_H_ */

