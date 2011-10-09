#ifndef _UT_CSTL_HASH_MAP_PRIVATE_H_
#define _UT_CSTL_HASH_MAP_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_hash_map_private)
/*
 * test _create_hash_map
 */
UT_CASE_DECLARATION(_create_hash_map)
void test__create_hash_map__null_typename(void** state);
void test__create_hash_map__c_builtin(void** state);
void test__create_hash_map__cstr(void** state);
void test__create_hash_map__libcstl_builtin(void** state);
void test__create_hash_map__user_define(void** state);
void test__create_hash_map__unregister(void** state);
/*
 * test _create_hash_map_auxiliary
 */
UT_CASE_DECLARATION(_create_hash_map_auxiliary)
void test__create_hash_map_auxiliary__null_hash_map(void** state);
void test__create_hash_map_auxiliary__null_typename(void** state);
void test__create_hash_map_auxiliary__unregistered(void** state);
void test__create_hash_map_auxiliary__c_builtin(void** state);
void test__create_hash_map_auxiliary__cstr(void** state);
void test__create_hash_map_auxiliary__libcstl_builtin(void** state);
void test__create_hash_map_auxiliary__user_define(void** state);
/*
 * test _hash_map_destroy_auxiliary
 */
UT_CASE_DECLARATION(_hash_map_destroy_auxiliary)
void test__hash_map_destroy_auxiliary__null_hash_map(void** state);
void test__hash_map_destroy_auxiliary__non_created(void** state);
void test__hash_map_destroy_auxiliary__non_inited(void** state);
void test__hash_map_destroy_auxiliary__empty(void** state);
void test__hash_map_destroy_auxiliary__non_empty(void** state);
/*
 * test _hash_map_find and _hash_map_find_varg
 */
UT_CASE_DECLARATION(_hash_map_find__hash_map_find_varg)
void test__hash_map_find__hash_map_find_varg__null_hash_map(void** state);
void test__hash_map_find__hash_map_find_varg__non_inited(void** state);
void test__hash_map_find__hash_map_find_varg__non_inited_pair(void** state);
void test__hash_map_find__hash_map_find_varg__c_builtin_find(void** state);
void test__hash_map_find__hash_map_find_varg__c_builtin_not_find(void** state);
void test__hash_map_find__hash_map_find_varg__cstr_find(void** state);
void test__hash_map_find__hash_map_find_varg__cstr_not_find(void** state);
void test__hash_map_find__hash_map_find_varg__libcstl_builtin_find(void** state);
void test__hash_map_find__hash_map_find_varg__libcstl_builtin_not_find(void** state);
void test__hash_map_find__hash_map_find_varg__user_define_find(void** state);
void test__hash_map_find__hash_map_find_varg__user_define_not_find(void** state);
/*
 * test _hash_map_count and _hash_map_count_varg
 */
UT_CASE_DECLARATION(_hash_map_count__hash_map_count_varg)
void test__hash_map_count__hash_map_count_varg__null_hash_map(void** state);
void test__hash_map_count__hash_map_count_varg__non_inited(void** state);
void test__hash_map_count__hash_map_count_varg__non_inited_pair(void** state);
void test__hash_map_count__hash_map_count_varg__c_builtin_0(void** state);
void test__hash_map_count__hash_map_count_varg__c_builtin_1(void** state);
void test__hash_map_count__hash_map_count_varg__c_builtin_n(void** state);
void test__hash_map_count__hash_map_count_varg__cstr_0(void** state);
void test__hash_map_count__hash_map_count_varg__cstr_1(void** state);
void test__hash_map_count__hash_map_count_varg__cstr_n(void** state);
void test__hash_map_count__hash_map_count_varg__libcstl_builtin_0(void** state);
void test__hash_map_count__hash_map_count_varg__libcstl_builtin_1(void** state);
void test__hash_map_count__hash_map_count_varg__libcstl_builtin_n(void** state);
void test__hash_map_count__hash_map_count_varg__user_define_0(void** state);
void test__hash_map_count__hash_map_count_varg__user_define_1(void** state);
void test__hash_map_count__hash_map_count_varg__user_define_n(void** state);
/*
 * test _hash_map_equal_range and _hash_map_equal_range_varg
 */
UT_CASE_DECLARATION(_hash_map_equal_range__hash_map_equal_range_varg)
void test__hash_map_equal_range__hash_map_equal_range_varg__null_hash_map(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__non_inited(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__non_inited_pair(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_equal(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_greater(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__cstr_upper_equal(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__cstr_greater(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_equal(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_greater(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__user_define_equal(void** state);
void test__hash_map_equal_range__hash_map_equal_range_varg__user_define_greater(void** state);
/*
 * test _hash_map_at and _hash_map_at_varg
 */
UT_CASE_DECLARATION(_hash_map_at__hash_map_at_varg)
void test__hash_map_at__hash_map_at_varg__null_hash_map(void** state);
void test__hash_map_at__hash_map_at_varg__non_inited(void** state);
void test__hash_map_at__hash_map_at_varg__non_inited_pair(void** state);
void test__hash_map_at__hash_map_at_varg__c_builtin_exist(void** state);
void test__hash_map_at__hash_map_at_varg__c_builtin_no_exist(void** state);
void test__hash_map_at__hash_map_at_varg__cstr_exist(void** state);
void test__hash_map_at__hash_map_at_varg__cstr_no_exist(void** state);
void test__hash_map_at__hash_map_at_varg__libcstl_builtin_exist(void** state);
void test__hash_map_at__hash_map_at_varg__libcstl_builtin_no_exist(void** state);
void test__hash_map_at__hash_map_at_varg__user_define_exist(void** state);
void test__hash_map_at__hash_map_at_varg__user_define_no_exist(void** state);
/*
 * test _hash_map_erase and _hash_map_erase_varg
 */
UT_CASE_DECLARATION(_hash_map_erase__hash_map_erase_varg)
void test__hash_map_erase__hash_map_erase_varg__null_hash_map(void** state);
void test__hash_map_erase__hash_map_erase_varg__non_inited(void** state);
void test__hash_map_erase__hash_map_erase_varg__non_inited_pair(void** state);
void test__hash_map_erase__hash_map_erase_varg__c_builtin_0(void** state);
void test__hash_map_erase__hash_map_erase_varg__c_builtin_1(void** state);
void test__hash_map_erase__hash_map_erase_varg__c_builtin_n(void** state);
void test__hash_map_erase__hash_map_erase_varg__cstr_0(void** state);
void test__hash_map_erase__hash_map_erase_varg__cstr_1(void** state);
void test__hash_map_erase__hash_map_erase_varg__cstr_n(void** state);
void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_0(void** state);
void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_1(void** state);
void test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_n(void** state);
void test__hash_map_erase__hash_map_erase_varg__user_define_0(void** state);
void test__hash_map_erase__hash_map_erase_varg__user_define_1(void** state);
void test__hash_map_erase__hash_map_erase_varg__user_define_n(void** state);
/*
 * test _hash_map_init_elem_auxiliary
 */
UT_CASE_DECLARATION(_hash_map_init_elem_auxiliary)
void test__hash_map_init_elem_auxiliary__null_hash_map_container(void** state);
void test__hash_map_init_elem_auxiliary__null_elem(void** state);
void test__hash_map_init_elem_auxiliary__non_inited(void** state);
void test__hash_map_init_elem_auxiliary__successfully_int(void** state);
void test__hash_map_init_elem_auxiliary__successfully_cstr(void** state);
void test__hash_map_init_elem_auxiliary__successfully_iterator(void** state);
void test__hash_map_init_elem_auxiliary__successfully_container(void** state);
void test__hash_map_init_elem_auxiliary__successfully_user_defined(void** state);

#define UT_CSTL_HASH_MAP_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_hash_map_private, test__create_hash_map__null_typename),\
    UT_CASE(test__create_hash_map__c_builtin),\
    UT_CASE(test__create_hash_map__cstr),\
    UT_CASE(test__create_hash_map__libcstl_builtin),\
    UT_CASE(test__create_hash_map__user_define),\
    UT_CASE(test__create_hash_map__unregister),\
    UT_CASE_BEGIN(_create_hash_map_auxiliary, test__create_hash_map_auxiliary__null_hash_map),\
    UT_CASE(test__create_hash_map_auxiliary__null_typename),\
    UT_CASE(test__create_hash_map_auxiliary__unregistered),\
    UT_CASE(test__create_hash_map_auxiliary__c_builtin),\
    UT_CASE(test__create_hash_map_auxiliary__cstr),\
    UT_CASE(test__create_hash_map_auxiliary__libcstl_builtin),\
    UT_CASE(test__create_hash_map_auxiliary__user_define),\
    UT_CASE_BEGIN(_hash_map_destroy_auxiliary, test__hash_map_destroy_auxiliary__null_hash_map),\
    UT_CASE(test__hash_map_destroy_auxiliary__non_created),\
    UT_CASE(test__hash_map_destroy_auxiliary__non_inited),\
    UT_CASE(test__hash_map_destroy_auxiliary__empty),\
    UT_CASE(test__hash_map_destroy_auxiliary__non_empty),\
    UT_CASE_BEGIN(_hash_map_find__hash_map_find_varg, test__hash_map_find__hash_map_find_varg__null_hash_map),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__non_inited),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__non_inited_pair),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__c_builtin_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__c_builtin_not_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__cstr_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__cstr_not_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__libcstl_builtin_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__libcstl_builtin_not_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__user_define_find),\
    UT_CASE(test__hash_map_find__hash_map_find_varg__user_define_not_find),\
    UT_CASE_BEGIN(_hash_map_count__hash_map_count_varg, test__hash_map_count__hash_map_count_varg__null_hash_map),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__non_inited),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__non_inited_pair),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__c_builtin_0),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__c_builtin_1),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__c_builtin_n),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__cstr_0),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__cstr_1),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__cstr_n),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__libcstl_builtin_0),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__libcstl_builtin_1),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__libcstl_builtin_n),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__user_define_0),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__user_define_1),\
    UT_CASE(test__hash_map_count__hash_map_count_varg__user_define_n),\
    UT_CASE_BEGIN(_hash_map_equal_range__hash_map_equal_range_varg, test__hash_map_equal_range__hash_map_equal_range_varg__null_hash_map),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__non_inited),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__non_inited_pair),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_equal),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__c_builtin_greater),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__cstr_upper_equal),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__cstr_greater),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_equal),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__libcstl_builtin_greater),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__user_define_equal),\
    UT_CASE(test__hash_map_equal_range__hash_map_equal_range_varg__user_define_greater),\
    UT_CASE_BEGIN(_hash_map_at__hash_map_at_varg, test__hash_map_at__hash_map_at_varg__null_hash_map),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__non_inited),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__non_inited_pair),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__c_builtin_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__c_builtin_no_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__cstr_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__cstr_no_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__libcstl_builtin_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__libcstl_builtin_no_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__user_define_exist),\
    UT_CASE(test__hash_map_at__hash_map_at_varg__user_define_no_exist),\
    UT_CASE_BEGIN(_hash_map_erase__hash_map_erase_varg, test__hash_map_erase__hash_map_erase_varg__null_hash_map),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__non_inited),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__non_inited_pair),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__c_builtin_0),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__c_builtin_1),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__c_builtin_n),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__cstr_0),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__cstr_1),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__cstr_n),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_0),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_1),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__libcstl_builtin_n),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__user_define_0),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__user_define_1),\
    UT_CASE(test__hash_map_erase__hash_map_erase_varg__user_define_n),\
    UT_CASE_BEGIN(_hash_map_init_elem_auxiliary, test__hash_map_init_elem_auxiliary__null_hash_map_container),\
    UT_CASE(test__hash_map_init_elem_auxiliary__null_elem),\
    UT_CASE(test__hash_map_init_elem_auxiliary__non_inited),\
    UT_CASE(test__hash_map_init_elem_auxiliary__successfully_int),\
    UT_CASE(test__hash_map_init_elem_auxiliary__successfully_cstr),\
    UT_CASE(test__hash_map_init_elem_auxiliary__successfully_iterator),\
    UT_CASE(test__hash_map_init_elem_auxiliary__successfully_container),\
    UT_CASE(test__hash_map_init_elem_auxiliary__successfully_user_defined)

#endif /* _UT_CSTL_HASH_MAP_PRIVATE_H_ */

