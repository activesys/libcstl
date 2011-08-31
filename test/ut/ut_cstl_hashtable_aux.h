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
UT_CASE_DECLARATION(_hashtable_is_inited)
void test__hashtable_is_inited__null_hashtable(void** state);
void test__hashtable_is_inited__invalid_typeinfo_style(void** state);
void test__hashtable_is_inited__invalid_typeinfo_type(void** state);
void test__hashtable_is_inited__invalid_hash(void** state);
void test__hashtable_is_inited__invalid_compare(void** state);
void test__hashtable_is_inited__invalid_bucket(void** state);
void test__hashtable_is_inited__inited(void** state);
/*
 * test _hashtable_iterator_belong_to_hashtable
 */
UT_CASE_DECLARATION(_hashtable_iterator_belong_to_hashtable)
void test__hashtable_iterator_belong_to_hashtable__null_hashtable(void** state);
void test__hashtable_iterator_belong_to_hashtable__non_inited(void** state);
void test__hashtable_iterator_belong_to_hashtable__null_bucketpos(void** state);
void test__hashtable_iterator_belong_to_hashtable__null_hashtablepos(void** state);
void test__hashtable_iterator_belong_to_hashtable__begin(void** state);
void test__hashtable_iterator_belong_to_hashtable__end(void** state);
void test__hashtable_iterator_belong_to_hashtable__middle(void** state);
void test__hashtable_iterator_belong_to_hashtable__invalid_bucketpos(void** state);
void test__hashtable_iterator_belong_to_hashtable__invalid_corepos(void** state);
/*
 * test _hashtable_same_hashtable_iterator_type
 */
UT_CASE_DECLARATION(_hashtable_same_hashtable_iterator_type)
void test__hashtable_same_hashtable_iterator_type__null_hashtable(void** state);
void test__hashtable_same_hashtable_iterator_type__non_created(void** state);
void test__hashtable_same_hashtable_iterator_type__invalid_iter(void** state);
void test__hashtable_same_hashtable_iterator_type__same_container(void** state);
void test__hashtable_same_hashtable_iterator_type__same(void** state);
void test__hashtable_same_hashtable_iterator_type__not_same(void** state);
/*
 * test _hashtable_same_hashtable_iterator_type_ex
 */
UT_CASE_DECLARATION(_hashtable_same_hashtable_iterator_type_ex)
void test__hashtable_same_hashtable_iterator_type_ex__null_hashtable(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__non_created(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__invalid_iter(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__same_container(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__same(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__not_same_type(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__not_same_hash(void** state);
void test__hashtable_same_hashtable_iterator_type_ex__not_same_compare(void** state);
/*
 * test _hashtable_same_type
 */
UT_CASE_DECLARATION(_hashtable_same_type)
void test__hashtable_same_type__null_first(void** state);
void test__hashtable_same_type__null_second(void** state);
void test__hashtable_same_type__non_created_first(void** state);
void test__hashtable_same_type__non_created_second(void** state);
void test__hashtable_same_type__same_type(void** state);
void test__hashtable_same_type__not_same_type(void** state);
void test__hashtable_same_type__same_hashtable(void** state);
void test__hashtable_same_type__not_same_hash(void** state);
void test__hashtable_same_type__not_same_compare(void** state);
/*
 * test _hashtable_same_type_ex
 */
UT_CASE_DECLARATION(_hashtable_same_type_ex)
void test__hashtable_same_type_ex__null_first(void** state);
void test__hashtable_same_type_ex__null_second(void** state);
void test__hashtable_same_type_ex__non_created_first(void** state);
void test__hashtable_same_type_ex__non_created_second(void** state);
void test__hashtable_same_type_ex__same_type(void** state);
void test__hashtable_same_type_ex__not_same_type(void** state);
void test__hashtable_same_type_ex__same_hashtable(void** state);
void test__hashtable_same_type_ex__not_same_hash(void** state);
void test__hashtable_same_type_ex__not_same_compare(void** state);
/*
 * test _hashtable_get_prime
 */
UT_CASE_DECLARATION(_hashtable_get_prime)
void test__hashtable_get_prime__0(void** state);
void test__hashtable_get_prime__53(void** state);
void test__hashtable_get_prime__8000000(void** state);
void test__hashtable_get_prime__201326611(void** state);
void test__hashtable_get_prime__4294967290(void** state);
void test__hashtable_get_prime__4294967291(void** state);
void test__hashtable_get_prime__4294967295(void** state);

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
    UT_CASE_BEGIN(_hashtable_is_inited, test__hashtable_is_inited__null_hashtable),\
    UT_CASE(test__hashtable_is_inited__invalid_typeinfo_style),\
    UT_CASE(test__hashtable_is_inited__invalid_typeinfo_type),\
    UT_CASE(test__hashtable_is_inited__invalid_hash),\
    UT_CASE(test__hashtable_is_inited__invalid_compare),\
    UT_CASE(test__hashtable_is_inited__invalid_bucket),\
    UT_CASE(test__hashtable_is_inited__inited),\
    UT_CASE_BEGIN(_hashtable_iterator_belong_to_hashtable, test__hashtable_iterator_belong_to_hashtable__null_hashtable),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__non_inited),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__null_bucketpos),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__null_hashtablepos),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__begin),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__end),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__middle),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__invalid_bucketpos),\
    UT_CASE(test__hashtable_iterator_belong_to_hashtable__invalid_corepos),\
    UT_CASE_BEGIN(_hashtable_same_hashtable_iterator_type, test__hashtable_same_hashtable_iterator_type__null_hashtable),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type__non_created),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type__invalid_iter),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type__same_container),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type__same),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type__not_same),\
    UT_CASE_BEGIN(_hashtable_same_hashtable_iterator_type_ex, test__hashtable_same_hashtable_iterator_type_ex__null_hashtable),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__non_created),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__invalid_iter),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__same_container),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__same),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__not_same_type),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__not_same_hash),\
    UT_CASE(test__hashtable_same_hashtable_iterator_type_ex__not_same_compare),\
    UT_CASE_BEGIN(_hashtable_same_type, test__hashtable_same_type__null_first),\
    UT_CASE(test__hashtable_same_type__null_second),\
    UT_CASE(test__hashtable_same_type__non_created_first),\
    UT_CASE(test__hashtable_same_type__non_created_second),\
    UT_CASE(test__hashtable_same_type__same_type),\
    UT_CASE(test__hashtable_same_type__not_same_type),\
    UT_CASE(test__hashtable_same_type__same_hashtable),\
    UT_CASE(test__hashtable_same_type__not_same_hash),\
    UT_CASE(test__hashtable_same_type__not_same_compare),\
    UT_CASE_BEGIN(_hashtable_same_type_ex, test__hashtable_same_type_ex__null_first),\
    UT_CASE(test__hashtable_same_type_ex__null_second),\
    UT_CASE(test__hashtable_same_type_ex__non_created_first),\
    UT_CASE(test__hashtable_same_type_ex__non_created_second),\
    UT_CASE(test__hashtable_same_type_ex__same_type),\
    UT_CASE(test__hashtable_same_type_ex__not_same_type),\
    UT_CASE(test__hashtable_same_type_ex__same_hashtable),\
    UT_CASE(test__hashtable_same_type_ex__not_same_hash),\
    UT_CASE(test__hashtable_same_type_ex__not_same_compare),\
    UT_CASE_BEGIN(_hashtable_get_prime, test__hashtable_get_prime__0),\
    UT_CASE(test__hashtable_get_prime__53),\
    UT_CASE(test__hashtable_get_prime__8000000),\
    UT_CASE(test__hashtable_get_prime__201326611),\
    UT_CASE(test__hashtable_get_prime__4294967290),\
    UT_CASE(test__hashtable_get_prime__4294967291),\
    UT_CASE(test__hashtable_get_prime__4294967295),\

#endif /* _UT_CSTL_HASHTABLE_AUX_H_ */

