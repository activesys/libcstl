#ifndef _UT_CSTL_TYPES_AUX_H_
#define _UT_CSTL_TYPES_AUX_H_

UT_SUIT_DECLARATION(cstl_types_aux)
/*
 * test _type_hash
 */
UT_CASE_DECLARATION(_type_hash)
void test__type_hash__null_typename(void** state);
void test__type_hash__null_empty(void** state);
void test__type_hash__lessthan_bucketcount(void** state);
/*
 * test _type_register_c_builtin
 */
UT_CASE_DECLARATION(_type_register_c_builtin)
void test__type_register_c_builtin__all(void** state);
/*
 * test _type_register_cstl_builtin
 */
UT_CASE_DECLARATION(_type_register_cstl_builtin)
void test__type_register_cstl_builtin__all(void** state);
/*
 * test _type_init
 */
UT_CASE_DECLARATION(_type_init)
void test__type_init__all(void** state);
/*
 * test _type_is_registered
 */
UT_CASE_DECLARATION(_type_is_registered)
void test__type_is_registered__null_typename(void** state);
void test__type_is_registered__long_typename(void** state);
void test__type_is_registered__not_register(void** state);
void test__type_is_registered__register(void** state);
/*
 * test _type_cache_find
 */
UT_CASE_DECLARATION(_type_cache_find)
void test__type_cache_find__typename_null(void** state);
void test__type_cache_find__formalname_null(void** state);
void test__type_cache_find__not_find_empty(void** state);
void test__type_cache_find__not_find(void** state);
void test__type_cache_find__find(void** state);
/*
 * test _type_cache_update
 */
UT_CASE_DECLARATION(_type_cache_update)
void test__type_cache_update__typename_null(void** state);
void test__type_cache_update__formalname_null(void** state);
void test__type_cache_update__invalid_style(void** state);
void test__type_cache_update__empty(void** state);
void test__type_cache_update__not_empty(void** state);
void test__type_cache_update__round(void** state);

#define UT_CSTL_TYPES_AUX_CASE\
    UT_SUIT_BEGIN(cstl_types_aux, test__type_hash__null_typename),\
    UT_CASE(test__type_hash__null_empty),\
    UT_CASE(test__type_hash__lessthan_bucketcount),\
    UT_CASE_BEGIN(_type_register_c_builtin, test__type_register_c_builtin__all),\
    UT_CASE_BEGIN(_type_register_cstl_builtin, test__type_register_cstl_builtin__all),\
    UT_CASE_BEGIN(_type_init, test__type_init__all),\
    UT_CASE_BEGIN(_type_is_registered, test__type_is_registered__null_typename),\
    UT_CASE(test__type_is_registered__long_typename),\
    UT_CASE(test__type_is_registered__not_register),\
    UT_CASE(test__type_is_registered__register),\
    UT_CASE_BEGIN(_type_cache_find, test__type_cache_find__typename_null),\
    UT_CASE(test__type_cache_find__formalname_null),\
    UT_CASE(test__type_cache_find__not_find_empty),\
    UT_CASE(test__type_cache_find__not_find),\
    UT_CASE(test__type_cache_find__find),\
    UT_CASE_BEGIN(_type_cache_update, test__type_cache_update__typename_null),\
    UT_CASE(test__type_cache_update__formalname_null),\
    UT_CASE(test__type_cache_update__invalid_style),\
    UT_CASE(test__type_cache_update__empty),\
    UT_CASE(test__type_cache_update__not_empty),\
    UT_CASE(test__type_cache_update__round)

#endif /* _UT_CSTL_TYPES_AUX_H_ */

