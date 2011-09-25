#ifndef _UT_CSTL_HASH_MULTIMAP_AUX_H_
#define _UT_CSTL_HASH_MULTIMAP_AUX_H_

UT_SUIT_DECLARATION(cstl_hash_multimap_aux)
/*
 * test _hash_multimap_same_pair_type_ex
 */
UT_CASE_DECLARATION(_hash_multimap_same_pair_type_ex)
void test__hash_multimap_same_pair_type_ex__first_null(void** state);
void test__hash_multimap_same_pair_type_ex__second_null(void** state);
void test__hash_multimap_same_pair_type_ex__same_pair(void** state);
void test__hash_multimap_same_pair_type_ex__first_noninited(void** state);
void test__hash_multimap_same_pair_type_ex__second_noninited(void** state);
void test__hash_multimap_same_pair_type_ex__not_same_first_type(void** state);
void test__hash_multimap_same_pair_type_ex__not_same_second_type(void** state);
void test__hash_multimap_same_pair_type_ex__not_mapkeycompare(void** state);
void test__hash_multimap_same_pair_type_ex__not_mapvaluecompare(void** state);
void test__hash_multimap_same_pair_type_ex__same_type(void** state);
/*
 * test _hash_multimap_same_pair_type
 */
UT_CASE_DECLARATION(_hash_multimap_same_pair_type)
void test__hash_multimap_same_pair_type__first_null(void** state);
void test__hash_multimap_same_pair_type__second_null(void** state);
void test__hash_multimap_same_pair_type__same_pair(void** state);
void test__hash_multimap_same_pair_type__first_noninited(void** state);
void test__hash_multimap_same_pair_type__second_noninited(void** state);
void test__hash_multimap_same_pair_type__not_same_first_type(void** state);
void test__hash_multimap_same_pair_type__not_same_second_type(void** state);
void test__hash_multimap_same_pair_type__not_mapkeycompare(void** state);
void test__hash_multimap_same_pair_type__not_mapvaluecompare(void** state);
void test__hash_multimap_same_pair_type__same_type(void** state);
/*
 * test _hash_multimap_value_compare
 */
UT_CASE_DECLARATION(_hash_multimap_value_compare)
void test__hash_multimap_value_compare__null_first(void** state);
void test__hash_multimap_value_compare__null_second(void** state);
void test__hash_multimap_value_compare__null_output(void** state);
void test__hash_multimap_value_compare__noninited_first(void** state);
void test__hash_multimap_value_compare__noninited_second(void** state);
void test__hash_multimap_value_compare__not_same(void** state);
void test__hash_multimap_value_compare__no_mapkeycompare_result_true(void** state);
void test__hash_multimap_value_compare__no_mapkeycompare_result_false(void** state);
void test__hash_multimap_value_compare__user_mapkeycompare_result_true(void** state);
void test__hash_multimap_value_compare__user_mapkeycompare_result_false(void** state);
/*
 * test _hash_multimap_default_hash
 */
UT_CASE_DECLARATION(_hash_multimap_default_hash)
void test__hash_multimap_default_hash__null_input(void** state);
void test__hash_multimap_default_hash__null_output(void** state);
void test__hash_multimap_default_hash__int(void** state);
void test__hash_multimap_default_hash__cstr(void** state);

#define UT_CSTL_HASH_MULTIMAP_AUX_CASE\
    UT_SUIT_BEGIN(cstl_hash_multimap_aux, test__hash_multimap_same_pair_type_ex__first_null),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__second_null),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__same_pair),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__first_noninited),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__second_noninited),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__not_same_first_type),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__not_same_second_type),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__not_mapkeycompare),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__not_mapvaluecompare),\
    UT_CASE(test__hash_multimap_same_pair_type_ex__same_type),\
    UT_CASE_BEGIN(_hash_multimap_same_pair_type, test__hash_multimap_same_pair_type__first_null),\
    UT_CASE(test__hash_multimap_same_pair_type__second_null),\
    UT_CASE(test__hash_multimap_same_pair_type__same_pair),\
    UT_CASE(test__hash_multimap_same_pair_type__first_noninited),\
    UT_CASE(test__hash_multimap_same_pair_type__second_noninited),\
    UT_CASE(test__hash_multimap_same_pair_type__not_same_first_type),\
    UT_CASE(test__hash_multimap_same_pair_type__not_same_second_type),\
    UT_CASE(test__hash_multimap_same_pair_type__not_mapkeycompare),\
    UT_CASE(test__hash_multimap_same_pair_type__not_mapvaluecompare),\
    UT_CASE(test__hash_multimap_same_pair_type__same_type),\
    UT_CASE_BEGIN(_hash_multimap_value_compare, test__hash_multimap_value_compare__null_first),\
    UT_CASE(test__hash_multimap_value_compare__null_second),\
    UT_CASE(test__hash_multimap_value_compare__null_output),\
    UT_CASE(test__hash_multimap_value_compare__noninited_first),\
    UT_CASE(test__hash_multimap_value_compare__noninited_second),\
    UT_CASE(test__hash_multimap_value_compare__not_same),\
    UT_CASE(test__hash_multimap_value_compare__no_mapkeycompare_result_true),\
    UT_CASE(test__hash_multimap_value_compare__no_mapkeycompare_result_false),\
    UT_CASE(test__hash_multimap_value_compare__user_mapkeycompare_result_true),\
    UT_CASE(test__hash_multimap_value_compare__user_mapkeycompare_result_false),\
    UT_CASE_BEGIN(_hash_multimap_default_hash, test__hash_multimap_default_hash__null_input),\
    UT_CASE(test__hash_multimap_default_hash__null_output),\
    UT_CASE(test__hash_multimap_default_hash__int),\
    UT_CASE(test__hash_multimap_default_hash__cstr)

#endif /* _UT_CSTL_HASH_MULTIMAP_AUX_H_ */

