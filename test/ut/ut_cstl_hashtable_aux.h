#ifndef _UT_CSTL_HASHTABLE_AUX_H_
#define _UT_CSTL_HASHTABLE_AUX_H_

UT_SUIT_DECLARATION(cstl_hashtable_aux)
/*
 * test _hashtable_is_created
 */
UT_CASE_DECLARATION(_hashtable_is_created)
void test__hashtable_is_created__null_hashtable(void** state);
void test__hashtable_is_created__non_inited_allocator(void** state);
void test__hashtable_is_created__invalid_rbroot_bucket(void** state);
void test__hashtable_is_created__invalid_rbroot_hash(void** state);
void test__hashtable_is_created__invalid_compare(void** state);
void test__hashtable_is_created__invalid_nodecount(void** state);
void test__hashtable_is_created__invalid_typeinfo_style(void** state);
void test__hashtable_is_created__invalid_typeinfo_type(void** state);
void test__hashtable_is_created__created(void** state);
/*
 * test _hashtable_is_inited
 */
/*
UT_CASE_DECLARATION(_hashtable_is_inited)
void test__hashtable_is_inited__null_hashtable(void** state);
void test__hashtable_is_inited__invalid_typeinfo_style(void** state);
void test__hashtable_is_inited__invalid_typeinfo_type(void** state);
void test__hashtable_is_inited__invalid_rbroot_left(void** state);
void test__hashtable_is_inited__invalid_rbroot_right(void** state);
void test__hashtable_is_inited__invalid_rbroot_color(void** state);
void test__hashtable_is_inited__invalid_compare(void** state);
void test__hashtable_is_inited__inited(void** state);
*/

#define UT_CSTL_HASHTABLE_AUX_CASE\
    UT_SUIT_BEGIN(cstl_hashtable_aux, test__hashtable_is_created__null_hashtable),\
    UT_CASE(test__hashtable_is_created__non_inited_allocator),\
    UT_CASE(test__hashtable_is_created__invalid_rbroot_bucket),\
    UT_CASE(test__hashtable_is_created__invalid_rbroot_hash),\
    UT_CASE(test__hashtable_is_created__invalid_compare),\
    UT_CASE(test__hashtable_is_created__invalid_nodecount),\
    UT_CASE(test__hashtable_is_created__invalid_typeinfo_style),\
    UT_CASE(test__hashtable_is_created__invalid_typeinfo_type),\
    UT_CASE(test__hashtable_is_created__created),\
/*
    UT_CASE_BEGIN(_hashtable_is_inited, test__hashtable_is_inited__null_hashtable),\
    UT_CASE(test__hashtable_is_inited__invalid_typeinfo_style),\
    UT_CASE(test__hashtable_is_inited__invalid_typeinfo_type),\
    UT_CASE(test__hashtable_is_inited__invalid_rbroot_left),\
    UT_CASE(test__hashtable_is_inited__invalid_rbroot_right),\
    UT_CASE(test__hashtable_is_inited__invalid_rbroot_color),\
    UT_CASE(test__hashtable_is_inited__invalid_compare),\
    UT_CASE(test__hashtable_is_inited__inited),\
    */

#endif /* _UT_CSTL_HASHTABLE_AUX_H_ */

