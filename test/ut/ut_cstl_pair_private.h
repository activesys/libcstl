#ifndef _UT_CSTL_PAIR_PRIVATE_H_
#define _UT_CSTL_PAIR_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_pair_private)
/*
 * test _pair_is_created
 */
UT_CASE_DECLARATION(_pair_is_created)
void test__pair_is_created__null_pair(void** state);
void test__pair_is_created__invalid_first(void** state);
void test__pair_is_created__invalid_second(void** state);
void test__pair_is_created__invalid_mapkeycompare(void** state);
void test__pair_is_created__invalid_mapvaluecompare(void** state);
void test__pair_is_created__invalid_typeinfofirst_style(void** state);
void test__pair_is_created__invalid_typeinfofirst_type(void** state);
void test__pair_is_created__invalid_typeinfosecond_style(void** state);
void test__pair_is_created__invalid_typeinfosecond_type(void** state);
void test__pair_is_created__created(void** state);

#define UT_CSTL_PAIR_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_pair_private, test__pair_is_created__null_pair),\
    UT_CASE(test__pair_is_created__invalid_first),\
    UT_CASE(test__pair_is_created__invalid_second),\
    UT_CASE(test__pair_is_created__invalid_mapkeycompare),\
    UT_CASE(test__pair_is_created__invalid_mapvaluecompare),\
    UT_CASE(test__pair_is_created__invalid_typeinfofirst_style),\
    UT_CASE(test__pair_is_created__invalid_typeinfofirst_type),\
    UT_CASE(test__pair_is_created__invalid_typeinfosecond_style),\
    UT_CASE(test__pair_is_created__invalid_typeinfosecond_type),\
    UT_CASE(test__pair_is_created__created),\

#endif /* _UT_CSTL_PAIR_PRIVATE_H_ */

