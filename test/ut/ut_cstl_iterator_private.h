#ifndef _UT_CSTL_ITERATOR_PRIVATE_H_
#define _UT_CSTL_ITERATOR_PRIVATE_H_

UT_SUIT_DECLARATION(cstl_iterator_private)

/*
 * test _iterator_is_valid
 */
UT_CASE_DECLARATION(_iterator_is_valid)
void test__iterator_is_valid__invalid_containertype(void** state);
void test__iterator_is_valid__invalid_iteratortype(void** state);
void test__iterator_is_valid__valid(void** state);
/*
 * test _iterator_get_pointer_ignore_cstr
 */
UT_CASE_DECLARATION(_iterator_get_pointer_ignore_cstr)
void test__iterator_get_pointer_ignore_cstr__invalid_iter(void** state);
void test__iterator_get_pointer_ignore_cstr__vector(void** state);
void test__iterator_get_pointer_ignore_cstr__vector_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__deque(void** state);
void test__iterator_get_pointer_ignore_cstr__deque_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__list(void** state);
void test__iterator_get_pointer_ignore_cstr__list_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__slist(void** state);
void test__iterator_get_pointer_ignore_cstr__slist_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__set(void** state);
void test__iterator_get_pointer_ignore_cstr__set_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__multiset(void** state);
void test__iterator_get_pointer_ignore_cstr__multiset_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__map(void** state);
void test__iterator_get_pointer_ignore_cstr__multimap(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_set(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_set_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_multiset(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_multiset_cstr(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_map(void** state);
void test__iterator_get_pointer_ignore_cstr__hash_multimap(void** state);
void test__iterator_get_pointer_ignore_cstr__string(void** state);
/*
 * test _iterator_same_type
 */
UT_CASE_DECLARATION(_iterator_same_type)
void test__iterator_same_type__invalid_first(void** state);
void test__iterator_same_type__invalid_second(void** state);
void test__iterator_same_type__containertype_not_equal(void** state);
void test__iterator_same_type__iteratortype_not_equal(void** state);
void test__iterator_same_type__same(void** state);
/*
 * test _iterator_before
 */
UT_CASE_DECLARATION(_iterator_before)
void test__iterator_before__invalid_first(void** state);
void test__iterator_before__invalid_second(void** state);
void test__iterator_before__containertype_not_equal(void** state);
void test__iterator_before__iteratortype_not_equal(void** state);
void test__iterator_before__vector_before(void** state);
void test__iterator_before__vector_equal(void** state);
void test__iterator_before__vector_after(void** state);
void test__iterator_before__deque_before(void** state);
void test__iterator_before__deque_equal(void** state);
void test__iterator_before__deque_after(void** state);
void test__iterator_before__list_before(void** state);
void test__iterator_before__list_equal(void** state);
void test__iterator_before__list_after(void** state);
void test__iterator_before__slist_before(void** state);
void test__iterator_before__slist_equal(void** state);
void test__iterator_before__slist_after(void** state);
void test__iterator_before__set_before(void** state);
void test__iterator_before__set_equal(void** state);
void test__iterator_before__set_after(void** state);
void test__iterator_before__multiset_before(void** state);
void test__iterator_before__multiset_equal(void** state);
void test__iterator_before__multiset_after(void** state);
void test__iterator_before__map_before(void** state);
void test__iterator_before__map_equal(void** state);
void test__iterator_before__map_after(void** state);
void test__iterator_before__multimap_before(void** state);
void test__iterator_before__multimap_equal(void** state);
void test__iterator_before__multimap_after(void** state);
void test__iterator_before__hash_set_before(void** state);
void test__iterator_before__hash_set_equal(void** state);
void test__iterator_before__hash_set_after(void** state);
void test__iterator_before__hash_multiset_before(void** state);
void test__iterator_before__hash_multiset_equal(void** state);
void test__iterator_before__hash_multiset_after(void** state);
void test__iterator_before__hash_map_before(void** state);
void test__iterator_before__hash_map_equal(void** state);
void test__iterator_before__hash_map_after(void** state);
void test__iterator_before__hash_multimap_before(void** state);
void test__iterator_before__hash_multimap_equal(void** state);
void test__iterator_before__hash_multimap_after(void** state);
void test__iterator_before__basic_string_before(void** state);
void test__iterator_before__basic_string_equal(void** state);
void test__iterator_before__basic_string_after(void** state);
/*
 * test _iterator_limit_type
 */
UT_CASE_DECLARATION(_iterator_limit_type)
void test__iterator_limit_type__invalid_iterator(void** state);
void test__iterator_limit_type__invalid_limittype(void** state);
void test__iterator_limit_type__input_iterator_true(void** state);
void test__iterator_limit_type__input_iterator_false(void** state);
void test__iterator_limit_type__output_iterator_true(void** state);
void test__iterator_limit_type__output_iterator_false(void** state);
void test__iterator_limit_type__forward_iterator_true(void** state);
void test__iterator_limit_type__forward_iterator_false(void** state);
void test__iterator_limit_type__bidirectional_iterator_true(void** state);
void test__iterator_limit_type__bidirectional_iterator_false(void** state);
void test__iterator_limit_type__random_access_iterator_true(void** state);
void test__iterator_limit_type__random_access_iterator_false(void** state);
/*
 * test _iterator_valid_range
 */
UT_CASE_DECLARATION(_iterator_valid_range)
void test__iterator_valid_range__invalid_first(void** state);
void test__iterator_valid_range__invalid_last(void** state);
void test__iterator_valid_range__invalid_type(void** state);
void test__iterator_valid_range__not_same(void** state);
void test__iterator_valid_range__limit_type(void** state);
void test__iterator_valid_range__equal(void** state);
void test__iterator_valid_range__before(void** state);
void test__iterator_valid_range__after(void** state);
/*
 * test _iterator_get_typeinfo
 */
UT_CASE_DECLARATION(_iterator_get_typeinfo)
void test__iterator_get_typeinfo__invalid(void** state);
void test__iterator_get_typeinfo__vector(void** state);
void test__iterator_get_typeinfo__deque(void** state);
void test__iterator_get_typeinfo__list(void** state);
void test__iterator_get_typeinfo__slist(void** state);
void test__iterator_get_typeinfo__set(void** state);
void test__iterator_get_typeinfo__multiset(void** state);
void test__iterator_get_typeinfo__map(void** state);
void test__iterator_get_typeinfo__multimap(void** state);
void test__iterator_get_typeinfo__hash_set(void** state);
void test__iterator_get_typeinfo__hash_multiset(void** state);
void test__iterator_get_typeinfo__hash_map(void** state);
void test__iterator_get_typeinfo__hash_multimap(void** state);
void test__iterator_get_typeinfo__string(void** state);
/*
 * test _iterator_get_typestyle
 */
UT_CASE_DECLARATION(_iterator_get_typestyle)
void test__iterator_get_typestyle__invalid(void** state);
void test__iterator_get_typestyle__c_builtin(void** state);
void test__iterator_get_typestyle__libcstl_builtin(void** state);
void test__iterator_get_typestyle__user_define(void** state);
/*
 * test _iterator_get_typebasename
 */
UT_CASE_DECLARATION(_iterator_get_typebasename)
void test__iterator_get_typebasename__invalid(void** state);
void test__iterator_get_typebasename__c_builtin(void** state);
void test__iterator_get_typebasename__libcstl_builtin(void** state);
void test__iterator_get_typebasename__user_define(void** state);
/*
 * test _iterator_get_typename
 */
UT_CASE_DECLARATION(_iterator_get_typename)
void test__iterator_get_typename__invalid(void** state);
void test__iterator_get_typename__c_builtin(void** state);
void test__iterator_get_typename__libcstl_builtin(void** state);
void test__iterator_get_typename__user_define(void** state);
/*
 * test _iterator_get_typecopy
 */
UT_CASE_DECLARATION(_iterator_get_typecopy)
void test__iterator_get_typecopy__invalid(void** state);
void test__iterator_get_typecopy__c_builtin(void** state);
void test__iterator_get_typecopy__cstl_builtin(void** state);
void test__iterator_get_typecopy__user_define_default(void** state);
void test__iterator_get_typecopy__user_define(void** state);
/*
 * test _iterator_get_typesize
 */
UT_CASE_DECLARATION(_iterator_get_typesize)
void test__iterator_get_typesize__invalid(void** state);
void test__iterator_get_typesize__c_builtin(void** state);
void test__iterator_get_typesize__cstl_builtin(void** state);
void test__iterator_get_typesize__user_define(void** state);
/*
 * test _iterator_same_elem_type
 */
UT_CASE_DECLARATION(_iterator_same_elem_type)
void test__iterator_same_elem_type__invalid_first(void** state);
void test__iterator_same_elem_type__invalid_second(void** state);
void test__iterator_same_elem_type__c_builtin_not_same(void** state);
void test__iterator_same_elem_type__c_builtin_same(void** state);
void test__iterator_same_elem_type__cstl_builtin_not_same_1(void** state);
void test__iterator_same_elem_type__cstl_builtin_not_same_2(void** state);
void test__iterator_same_elem_type__cstl_builtin_same(void** state);
void test__iterator_same_elem_type__user_define_not_same(void** state);
void test__iterator_same_elem_type__user_define_same(void** state);
void test__iterator_same_elem_type__not_same_container_not_same_type(void** state);
void test__iterator_same_elem_type__not_same_container_same_type(void** state);
/*
 * test _iterator_allocate_init_elem and _iterator_deallocate_destroy_elem
 */
UT_CASE_DECLARATION(_iterator_allocate_init_elem__iterator_deallocate_destroy_elem)
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__allocate_invalid(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deallocate_invalid(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__null_value(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_c_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_cstl_builtin(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_user_define(void** state);
void test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__string(void** state);

#define UT_CSTL_ITERATOR_PRIVATE_CASE\
    UT_SUIT_BEGIN(cstl_iterator_private, test__iterator_is_valid__invalid_containertype),\
    UT_CASE(test__iterator_is_valid__invalid_iteratortype),\
    UT_CASE(test__iterator_is_valid__valid),\
    UT_CASE_BEGIN(_iterator_get_pointer_ignore_cstr, test__iterator_get_pointer_ignore_cstr__invalid_iter),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__vector),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__vector_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__deque),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__deque_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__list),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__list_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__slist),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__slist_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__set),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__set_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__multiset),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__multiset_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__map),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__multimap),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_set),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_set_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_multiset),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_multiset_cstr),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_map),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__hash_multimap),\
    UT_CASE(test__iterator_get_pointer_ignore_cstr__string),\
    UT_CASE_BEGIN(_iterator_same_type, test__iterator_same_type__invalid_first),\
    UT_CASE(test__iterator_same_type__invalid_second),\
    UT_CASE(test__iterator_same_type__containertype_not_equal),\
    UT_CASE(test__iterator_same_type__iteratortype_not_equal),\
    UT_CASE(test__iterator_same_type__same),\
    UT_CASE_BEGIN(_iterator_before, test__iterator_before__invalid_first),\
    UT_CASE(test__iterator_before__invalid_second),\
    UT_CASE(test__iterator_before__containertype_not_equal),\
    UT_CASE(test__iterator_before__iteratortype_not_equal),\
    UT_CASE(test__iterator_before__vector_before),\
    UT_CASE(test__iterator_before__vector_equal),\
    UT_CASE(test__iterator_before__vector_after),\
    UT_CASE(test__iterator_before__deque_before),\
    UT_CASE(test__iterator_before__deque_equal),\
    UT_CASE(test__iterator_before__deque_after),\
    UT_CASE(test__iterator_before__list_before),\
    UT_CASE(test__iterator_before__list_equal),\
    UT_CASE(test__iterator_before__list_after),\
    UT_CASE(test__iterator_before__slist_before),\
    UT_CASE(test__iterator_before__slist_equal),\
    UT_CASE(test__iterator_before__slist_after),\
    UT_CASE(test__iterator_before__set_before),\
    UT_CASE(test__iterator_before__set_equal),\
    UT_CASE(test__iterator_before__set_after),\
    UT_CASE(test__iterator_before__multiset_before),\
    UT_CASE(test__iterator_before__multiset_equal),\
    UT_CASE(test__iterator_before__multiset_after),\
    UT_CASE(test__iterator_before__map_before),\
    UT_CASE(test__iterator_before__map_equal),\
    UT_CASE(test__iterator_before__map_after),\
    UT_CASE(test__iterator_before__multimap_before),\
    UT_CASE(test__iterator_before__multimap_equal),\
    UT_CASE(test__iterator_before__multimap_after),\
    UT_CASE(test__iterator_before__hash_set_before),\
    UT_CASE(test__iterator_before__hash_set_equal),\
    UT_CASE(test__iterator_before__hash_set_after),\
    UT_CASE(test__iterator_before__hash_multiset_before),\
    UT_CASE(test__iterator_before__hash_multiset_equal),\
    UT_CASE(test__iterator_before__hash_multiset_after),\
    UT_CASE(test__iterator_before__hash_map_before),\
    UT_CASE(test__iterator_before__hash_map_equal),\
    UT_CASE(test__iterator_before__hash_map_after),\
    UT_CASE(test__iterator_before__hash_multimap_before),\
    UT_CASE(test__iterator_before__hash_multimap_equal),\
    UT_CASE(test__iterator_before__hash_multimap_after),\
    UT_CASE(test__iterator_before__basic_string_before),\
    UT_CASE(test__iterator_before__basic_string_equal),\
    UT_CASE(test__iterator_before__basic_string_after),\
    UT_CASE_BEGIN(_iterator_limit_type, test__iterator_limit_type__invalid_iterator),\
    UT_CASE(test__iterator_limit_type__invalid_limittype),\
    UT_CASE(test__iterator_limit_type__input_iterator_true),\
    UT_CASE(test__iterator_limit_type__input_iterator_false),\
    UT_CASE(test__iterator_limit_type__output_iterator_true),\
    UT_CASE(test__iterator_limit_type__output_iterator_false),\
    UT_CASE(test__iterator_limit_type__forward_iterator_true),\
    UT_CASE(test__iterator_limit_type__forward_iterator_false),\
    UT_CASE(test__iterator_limit_type__bidirectional_iterator_true),\
    UT_CASE(test__iterator_limit_type__bidirectional_iterator_false),\
    UT_CASE(test__iterator_limit_type__random_access_iterator_true),\
    UT_CASE(test__iterator_limit_type__random_access_iterator_false),\
    UT_CASE_BEGIN(_iterator_valid_range, test__iterator_valid_range__invalid_first),\
    UT_CASE(test__iterator_valid_range__invalid_last),\
    UT_CASE(test__iterator_valid_range__invalid_type),\
    UT_CASE(test__iterator_valid_range__not_same),\
    UT_CASE(test__iterator_valid_range__limit_type),\
    UT_CASE(test__iterator_valid_range__equal),\
    UT_CASE(test__iterator_valid_range__before),\
    UT_CASE(test__iterator_valid_range__after),\
    UT_CASE_BEGIN(_iterator_get_typeinfo, test__iterator_get_typeinfo__invalid),\
    UT_CASE(test__iterator_get_typeinfo__vector),\
    UT_CASE(test__iterator_get_typeinfo__deque),\
    UT_CASE(test__iterator_get_typeinfo__list),\
    UT_CASE(test__iterator_get_typeinfo__slist),\
    UT_CASE(test__iterator_get_typeinfo__set),\
    UT_CASE(test__iterator_get_typeinfo__multiset),\
    UT_CASE(test__iterator_get_typeinfo__map),\
    UT_CASE(test__iterator_get_typeinfo__multimap),\
    UT_CASE(test__iterator_get_typeinfo__hash_set),\
    UT_CASE(test__iterator_get_typeinfo__hash_multiset),\
    UT_CASE(test__iterator_get_typeinfo__hash_map),\
    UT_CASE(test__iterator_get_typeinfo__hash_multimap),\
    UT_CASE(test__iterator_get_typeinfo__string),\
    UT_CASE_BEGIN(_iterator_get_typestyle, test__iterator_get_typestyle__invalid),\
    UT_CASE(test__iterator_get_typestyle__c_builtin),\
    UT_CASE(test__iterator_get_typestyle__libcstl_builtin),\
    UT_CASE(test__iterator_get_typestyle__user_define),\
    UT_CASE_BEGIN(_iterator_get_typebasename, test__iterator_get_typebasename__invalid),\
    UT_CASE(test__iterator_get_typebasename__c_builtin),\
    UT_CASE(test__iterator_get_typebasename__libcstl_builtin),\
    UT_CASE(test__iterator_get_typebasename__user_define),\
    UT_CASE_BEGIN(_iterator_get_typename, test__iterator_get_typename__invalid),\
    UT_CASE(test__iterator_get_typename__c_builtin),\
    UT_CASE(test__iterator_get_typename__libcstl_builtin),\
    UT_CASE(test__iterator_get_typename__user_define),\
    UT_CASE_BEGIN(_iterator_get_typecopy, test__iterator_get_typecopy__invalid),\
    UT_CASE(test__iterator_get_typecopy__c_builtin),\
    UT_CASE(test__iterator_get_typecopy__cstl_builtin),\
    UT_CASE(test__iterator_get_typecopy__user_define_default),\
    UT_CASE(test__iterator_get_typecopy__user_define),\
    UT_CASE_BEGIN(_iterator_get_typesize, test__iterator_get_typesize__invalid),\
    UT_CASE(test__iterator_get_typesize__c_builtin),\
    UT_CASE(test__iterator_get_typesize__cstl_builtin),\
    UT_CASE(test__iterator_get_typesize__user_define),\
    UT_CASE_BEGIN(_iterator_same_elem_type, test__iterator_same_elem_type__invalid_first),\
    UT_CASE(test__iterator_same_elem_type__invalid_second),\
    UT_CASE(test__iterator_same_elem_type__c_builtin_not_same),\
    UT_CASE(test__iterator_same_elem_type__c_builtin_same),\
    UT_CASE(test__iterator_same_elem_type__cstl_builtin_not_same_1),\
    UT_CASE(test__iterator_same_elem_type__cstl_builtin_not_same_2),\
    UT_CASE(test__iterator_same_elem_type__cstl_builtin_same),\
    UT_CASE(test__iterator_same_elem_type__user_define_not_same),\
    UT_CASE(test__iterator_same_elem_type__user_define_same),\
    UT_CASE(test__iterator_same_elem_type__not_same_container_not_same_type),\
    UT_CASE(test__iterator_same_elem_type__not_same_container_same_type),\
    UT_CASE_BEGIN(_iterator_allocate_init_elem__iterator_deallocate_destroy_elem, test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__allocate_invalid),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deallocate_invalid),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__null_value),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__vector_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__list_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__deque_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__slist_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__set_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multiset_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_set_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multiset_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__map_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__multimap_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_map_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_c_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_cstl_builtin),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__hash_multimap_user_define),\
    UT_CASE(test__iterator_allocate_init_elem__iterator_deallocate_destroy_elem__string)

#endif /* _UT_CSTL_ITERATOR_PRIVATE_H_ */

