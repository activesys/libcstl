#ifndef _UT_CSTL_ITERATOR_H_
#define _UT_CSTL_ITERATOR_H_

UT_SUIT_DECLARATION(cstl_iterator)

/*
 * test iterator_get_value
 */
UT_CASE_DECLARATION(iterator_get_value)
void test_iterator_get_value__invalid_iter(void** state);
void test_iterator_get_value__null(void** state);
void test_iterator_get_value__vector(void** state);
void test_iterator_get_value__deque(void** state);
void test_iterator_get_value__list(void** state);
void test_iterator_get_value__slist(void** state);
void test_iterator_get_value__set(void** state);
void test_iterator_get_value__multiset(void** state);
void test_iterator_get_value__map(void** state);
void test_iterator_get_value__multimap(void** state);
void test_iterator_get_value__hash_set(void** state);
void test_iterator_get_value__hash_multiset(void** state);
void test_iterator_get_value__hash_map(void** state);
void test_iterator_get_value__hash_multimap(void** state);
void test_iterator_get_value__string(void** state);

/*
 * test iterator_set_value
 */
UT_CASE_DECLARATION(iterator_set_value)
void test_iterator_set_value__invalid_iter(void** state);
void test_iterator_set_value__null(void** state);
void test_iterator_set_value__vector(void** state);
void test_iterator_set_value__deque(void** state);
void test_iterator_set_value__list(void** state);
void test_iterator_set_value__slist(void** state);
void test_iterator_set_value__set(void** state);
void test_iterator_set_value__multiset(void** state);
void test_iterator_set_value__map(void** state);
void test_iterator_set_value__multimap(void** state);
void test_iterator_set_value__hash_set(void** state);
void test_iterator_set_value__hash_multiset(void** state);
void test_iterator_set_value__hash_map(void** state);
void test_iterator_set_value__hash_multimap(void** state);
void test_iterator_set_value__string(void** state);

/*
 * test iterator_get_pointer
 */
UT_CASE_DECLARATION(iterator_get_pointer)
void test_iterator_get_pointer__invalid_iter(void** state);
void test_iterator_get_pointer__vector(void** state);
void test_iterator_get_pointer__deque(void** state);
void test_iterator_get_pointer__list(void** state);
void test_iterator_get_pointer__slist(void** state);
void test_iterator_get_pointer__set(void** state);
void test_iterator_get_pointer__multiset(void** state);
void test_iterator_get_pointer__map(void** state);
void test_iterator_get_pointer__multimap(void** state);
void test_iterator_get_pointer__hash_set(void** state);
void test_iterator_get_pointer__hash_multiset(void** state);
void test_iterator_get_pointer__hash_map(void** state);
void test_iterator_get_pointer__hash_multimap(void** state);
void test_iterator_get_pointer__string(void** state);

/*
 * test iterator_next
 */
UT_CASE_DECLARATION(iterator_next)
void test_iterator_next__invalid_iter(void** state);
void test_iterator_next__vector(void** state);
void test_iterator_next__vector_end(void** state);
void test_iterator_next__deque(void** state);
void test_iterator_next__deque_end(void** state);
void test_iterator_next__list(void** state);
void test_iterator_next__list_end(void** state);
void test_iterator_next__slist(void** state);
void test_iterator_next__slist_end(void** state);
void test_iterator_next__set(void** state);
void test_iterator_next__set_end(void** state);
void test_iterator_next__multiset(void** state);
void test_iterator_next__multiset_end(void** state);
void test_iterator_next__map(void** state);
void test_iterator_next__map_end(void** state);
void test_iterator_next__multimap(void** state);
void test_iterator_next__multimap_end(void** state);
void test_iterator_next__hash_set(void** state);
void test_iterator_next__hash_set_end(void** state);
void test_iterator_next__hash_multiset(void** state);
void test_iterator_next__hash_multiset_end(void** state);
void test_iterator_next__hash_map(void** state);
void test_iterator_next__hash_map_end(void** state);
void test_iterator_next__hash_multimap(void** state);
void test_iterator_next__hash_multimap_end(void** state);
void test_iterator_next__string(void** state);
void test_iterator_next__string_end(void** state);

/*
 * test iterator_prev
 */
UT_CASE_DECLARATION(iterator_prev)
void test_iterator_prev__invalid_iter(void** state);
void test_iterator_prev__vector(void** state);
void test_iterator_prev__vector_begin(void** state);
void test_iterator_prev__deque(void** state);
void test_iterator_prev__deque_begin(void** state);
void test_iterator_prev__list(void** state);
void test_iterator_prev__list_begin(void** state);
void test_iterator_prev__slist(void** state);
void test_iterator_prev__slist_begin(void** state);
void test_iterator_prev__set(void** state);
void test_iterator_prev__set_begin(void** state);
void test_iterator_prev__multiset(void** state);
void test_iterator_prev__multiset_begin(void** state);
void test_iterator_prev__map(void** state);
void test_iterator_prev__map_begin(void** state);
void test_iterator_prev__multimap(void** state);
void test_iterator_prev__multimap_begin(void** state);
void test_iterator_prev__hash_set(void** state);
void test_iterator_prev__hash_set_begin(void** state);
void test_iterator_prev__hash_multiset(void** state);
void test_iterator_prev__hash_multiset_begin(void** state);
void test_iterator_prev__hash_map(void** state);
void test_iterator_prev__hash_map_begin(void** state);
void test_iterator_prev__hash_multimap(void** state);
void test_iterator_prev__hash_multimap_begin(void** state);
void test_iterator_prev__string(void** state);
void test_iterator_prev__string_begin(void** state);

/*
 * test iterator_next_n
 */
UT_CASE_DECLARATION(iterator_next_n)
void test_iterator_next_n__invalid_iter(void** state);
void test_iterator_next_n__vector_0(void** state);
void test_iterator_next_n__vector_n(void** state);
void test_iterator_next_n__vector_n_(void** state);
void test_iterator_next_n__vector_end_n(void** state);
void test_iterator_next_n__vector_prev_n(void** state);
void test_iterator_next_n__deque_0(void** state);
void test_iterator_next_n__deque_n(void** state);
void test_iterator_next_n__deque_n_(void** state);
void test_iterator_next_n__deque_end_n(void** state);
void test_iterator_next_n__deque_prev_n(void** state);
void test_iterator_next_n__list(void** state);
void test_iterator_next_n__slist(void** state);
void test_iterator_next_n__set(void** state);
void test_iterator_next_n__multiset(void** state);
void test_iterator_next_n__map(void** state);
void test_iterator_next_n__multimap(void** state);
void test_iterator_next_n__hash_set(void** state);
void test_iterator_next_n__hash_multiset(void** state);
void test_iterator_next_n__hash_map(void** state);
void test_iterator_next_n__hash_multimap(void** state);
void test_iterator_next_n__string_0(void** state);
void test_iterator_next_n__string_n(void** state);
void test_iterator_next_n__string_n_(void** state);
void test_iterator_next_n__string_end_n(void** state);
void test_iterator_next_n__string_prev_n(void** state);

/*
 * test iterator_prev_n
 */
UT_CASE_DECLARATION(iterator_prev_n)
void test_iterator_prev_n__invalid_iter(void** state);
void test_iterator_prev_n__vector_0(void** state);
void test_iterator_prev_n__vector_n(void** state);
void test_iterator_prev_n__vector_n_(void** state);
void test_iterator_prev_n__vector_end_n(void** state);
void test_iterator_prev_n__vector_prev_n(void** state);
void test_iterator_prev_n__deque_0(void** state);
void test_iterator_prev_n__deque_n(void** state);
void test_iterator_prev_n__deque_n_(void** state);
void test_iterator_prev_n__deque_end_n(void** state);
void test_iterator_prev_n__deque_prev_n(void** state);
void test_iterator_prev_n__list(void** state);
void test_iterator_prev_n__slist(void** state);
void test_iterator_prev_n__set(void** state);
void test_iterator_prev_n__multiset(void** state);
void test_iterator_prev_n__map(void** state);
void test_iterator_prev_n__multimap(void** state);
void test_iterator_prev_n__hash_set(void** state);
void test_iterator_prev_n__hash_multiset(void** state);
void test_iterator_prev_n__hash_map(void** state);
void test_iterator_prev_n__hash_multimap(void** state);
void test_iterator_prev_n__string_0(void** state);
void test_iterator_prev_n__string_n(void** state);
void test_iterator_prev_n__string_n_(void** state);
void test_iterator_prev_n__string_end_n(void** state);
void test_iterator_prev_n__string_prev_n(void** state);

/*
 * test iterator_equal
 */
UT_CASE_DECLARATION(iterator_equal)
void test_iterator_equal__invalid_first(void** state);
void test_iterator_equal__invalid_second(void** state);
void test_iterator_equal__vector_equal(void** state);
void test_iterator_equal__vector_not_equal(void** state);
void test_iterator_equal__deque_equal(void** state);
void test_iterator_equal__deque_not_equal(void** state);
void test_iterator_equal__list_equal(void** state);
void test_iterator_equal__list_not_equal(void** state);
void test_iterator_equal__slist_equal(void** state);
void test_iterator_equal__slist_not_equal(void** state);
void test_iterator_equal__set_equal(void** state);
void test_iterator_equal__set_not_equal(void** state);
void test_iterator_equal__multiset_equal(void** state);
void test_iterator_equal__multiset_not_equal(void** state);
void test_iterator_equal__map_equal(void** state);
void test_iterator_equal__map_not_equal(void** state);
void test_iterator_equal__multimap_equal(void** state);
void test_iterator_equal__multimap_not_equal(void** state);
void test_iterator_equal__hash_set_equal(void** state);
void test_iterator_equal__hash_set_not_equal(void** state);
void test_iterator_equal__hash_multiset_equal(void** state);
void test_iterator_equal__hash_multiset_not_equal(void** state);
void test_iterator_equal__hash_map_equal(void** state);
void test_iterator_equal__hash_map_not_equal(void** state);
void test_iterator_equal__hash_multimap_equal(void** state);
void test_iterator_equal__hash_multimap_not_equal(void** state);
void test_iterator_equal__string_equal(void** state);
void test_iterator_equal__string_not_equal(void** state);

/*
 * test iterator_not_equal
 */
UT_CASE_DECLARATION(iterator_not_equal)
void test_iterator_not_equal__invalid_first(void** state);
void test_iterator_not_equal__invalid_second(void** state);
void test_iterator_not_equal__vector_equal(void** state);
void test_iterator_not_equal__vector_not_equal(void** state);
void test_iterator_not_equal__deque_equal(void** state);
void test_iterator_not_equal__deque_not_equal(void** state);
void test_iterator_not_equal__list_equal(void** state);
void test_iterator_not_equal__list_not_equal(void** state);
void test_iterator_not_equal__slist_equal(void** state);
void test_iterator_not_equal__slist_not_equal(void** state);
void test_iterator_not_equal__set_equal(void** state);
void test_iterator_not_equal__set_not_equal(void** state);
void test_iterator_not_equal__multiset_equal(void** state);
void test_iterator_not_equal__multiset_not_equal(void** state);
void test_iterator_not_equal__map_equal(void** state);
void test_iterator_not_equal__map_not_equal(void** state);
void test_iterator_not_equal__multimap_equal(void** state);
void test_iterator_not_equal__multimap_not_equal(void** state);
void test_iterator_not_equal__hash_set_equal(void** state);
void test_iterator_not_equal__hash_set_not_equal(void** state);
void test_iterator_not_equal__hash_multiset_equal(void** state);
void test_iterator_not_equal__hash_multiset_not_equal(void** state);
void test_iterator_not_equal__hash_map_equal(void** state);
void test_iterator_not_equal__hash_map_not_equal(void** state);
void test_iterator_not_equal__hash_multimap_equal(void** state);
void test_iterator_not_equal__hash_multimap_not_equal(void** state);
void test_iterator_not_equal__string_equal(void** state);
void test_iterator_not_equal__string_not_equal(void** state);

/*
 * test iteator_less
 */
UT_CASE_DECLARATION(iterator_less)
void test_iterator_less__invalid_first(void** state);
void test_iterator_less__invalid_second(void** state);
void test_iterator_less__vector_less(void** state);
void test_iterator_less__vector_equal(void** state);
void test_iterator_less__vector_greater(void** state);
void test_iterator_less__deque_less(void** state);
void test_iterator_less__deque_equal(void** state);
void test_iterator_less__deque_greater(void** state);
void test_iterator_less__list(void** state);
void test_iterator_less__slist(void** state);
void test_iterator_less__set(void** state);
void test_iterator_less__multiset(void** state);
void test_iterator_less__map(void** state);
void test_iterator_less__multimap(void** state);
void test_iterator_less__hash_set(void** state);
void test_iterator_less__hash_multiset(void** state);
void test_iterator_less__hash_map(void** state);
void test_iterator_less__hash_multimap(void** state);
void test_iterator_less__string_less(void** state);
void test_iterator_less__string_equal(void** state);
void test_iterator_less__string_greater(void** state);

/*
 * test iteator_less_equal
 */
UT_CASE_DECLARATION(iterator_less_equal)
void test_iterator_less_equal__invalid_first(void** state);
void test_iterator_less_equal__invalid_second(void** state);
void test_iterator_less_equal__vector_less(void** state);
void test_iterator_less_equal__vector_equal(void** state);
void test_iterator_less_equal__vector_greater(void** state);
void test_iterator_less_equal__deque_less(void** state);
void test_iterator_less_equal__deque_equal(void** state);
void test_iterator_less_equal__deque_greater(void** state);
void test_iterator_less_equal__list(void** state);
void test_iterator_less_equal__slist(void** state);
void test_iterator_less_equal__set(void** state);
void test_iterator_less_equal__multiset(void** state);
void test_iterator_less_equal__map(void** state);
void test_iterator_less_equal__multimap(void** state);
void test_iterator_less_equal__hash_set(void** state);
void test_iterator_less_equal__hash_multiset(void** state);
void test_iterator_less_equal__hash_map(void** state);
void test_iterator_less_equal__hash_multimap(void** state);
void test_iterator_less_equal__string_less(void** state);
void test_iterator_less_equal__string_equal(void** state);
void test_iterator_less_equal__string_greater(void** state);

/*
 * test iteator_greater
 */
UT_CASE_DECLARATION(iterator_greater)
void test_iterator_greater__invalid_first(void** state);
void test_iterator_greater__invalid_second(void** state);
void test_iterator_greater__vector_less(void** state);
void test_iterator_greater__vector_equal(void** state);
void test_iterator_greater__vector_greater(void** state);
void test_iterator_greater__deque_less(void** state);
void test_iterator_greater__deque_equal(void** state);
void test_iterator_greater__deque_greater(void** state);
void test_iterator_greater__list(void** state);
void test_iterator_greater__slist(void** state);
void test_iterator_greater__set(void** state);
void test_iterator_greater__multiset(void** state);
void test_iterator_greater__map(void** state);
void test_iterator_greater__multimap(void** state);
void test_iterator_greater__hash_set(void** state);
void test_iterator_greater__hash_multiset(void** state);
void test_iterator_greater__hash_map(void** state);
void test_iterator_greater__hash_multimap(void** state);
void test_iterator_greater__string_less(void** state);
void test_iterator_greater__string_equal(void** state);
void test_iterator_greater__string_greater(void** state);

/*
 * test iteator_greater
 */
UT_CASE_DECLARATION(iterator_greater_equal)
void test_iterator_greater_equal__invalid_first(void** state);
void test_iterator_greater_equal__invalid_second(void** state);
void test_iterator_greater_equal__vector_less(void** state);
void test_iterator_greater_equal__vector_equal(void** state);
void test_iterator_greater_equal__vector_greater(void** state);
void test_iterator_greater_equal__deque_less(void** state);
void test_iterator_greater_equal__deque_equal(void** state);
void test_iterator_greater_equal__deque_greater(void** state);
void test_iterator_greater_equal__list(void** state);
void test_iterator_greater_equal__slist(void** state);
void test_iterator_greater_equal__set(void** state);
void test_iterator_greater_equal__multiset(void** state);
void test_iterator_greater_equal__map(void** state);
void test_iterator_greater_equal__multimap(void** state);
void test_iterator_greater_equal__hash_set(void** state);
void test_iterator_greater_equal__hash_multiset(void** state);
void test_iterator_greater_equal__hash_map(void** state);
void test_iterator_greater_equal__hash_multimap(void** state);
void test_iterator_greater_equal__string_less(void** state);
void test_iterator_greater_equal__string_equal(void** state);
void test_iterator_greater_equal__string_greater(void** state);

/*
 * test iterator_at
 */
UT_CASE_DECLARATION(iterator_at)
void test_iterator_at__invalid_iter(void** state);
void test_iterator_at__vector_0(void** state);
void test_iterator_at__vector_n(void** state);
void test_iterator_at__vector_n_(void** state);
void test_iterator_at__vector_end_n(void** state);
void test_iterator_at__vector_prev_n(void** state);
void test_iterator_at__deque_0(void** state);
void test_iterator_at__deque_n(void** state);
void test_iterator_at__deque_n_(void** state);
void test_iterator_at__deque_end_n(void** state);
void test_iterator_at__deque_prev_n(void** state);
void test_iterator_at__list(void** state);
void test_iterator_at__slist(void** state);
void test_iterator_at__set(void** state);
void test_iterator_at__multiset(void** state);
void test_iterator_at__map(void** state);
void test_iterator_at__multimap(void** state);
void test_iterator_at__hash_set(void** state);
void test_iterator_at__hash_multiset(void** state);
void test_iterator_at__hash_map(void** state);
void test_iterator_at__hash_multimap(void** state);
void test_iterator_at__string_0(void** state);
void test_iterator_at__string_n(void** state);
void test_iterator_at__string_n_(void** state);
void test_iterator_at__string_end_n(void** state);
void test_iterator_at__string_prev_n(void** state);

/*
 * test iteator_less
 */
UT_CASE_DECLARATION(iterator_minus)
void test_iterator_minus__invalid_first(void** state);
void test_iterator_minus__invalid_second(void** state);
void test_iterator_minus__not_same_container(void** state);
void test_iterator_minus__vector_less(void** state);
void test_iterator_minus__vector_equal(void** state);
void test_iterator_minus__vector_greater(void** state);
void test_iterator_minus__deque_less(void** state);
void test_iterator_minus__deque_equal(void** state);
void test_iterator_minus__deque_greater(void** state);
void test_iterator_minus__list(void** state);
void test_iterator_minus__slist(void** state);
void test_iterator_minus__set(void** state);
void test_iterator_minus__multiset(void** state);
void test_iterator_minus__map(void** state);
void test_iterator_minus__multimap(void** state);
void test_iterator_minus__hash_set(void** state);
void test_iterator_minus__hash_multiset(void** state);
void test_iterator_minus__hash_map(void** state);
void test_iterator_minus__hash_multimap(void** state);
void test_iterator_minus__string_less(void** state);
void test_iterator_minus__string_equal(void** state);
void test_iterator_minus__string_greater(void** state);

/*
 * test iteator_distance
 */
UT_CASE_DECLARATION(iterator_distance)
void test_iterator_distance__invalid_first(void** state);
void test_iterator_distance__invalid_second(void** state);
void test_iterator_distance__not_same_container(void** state);
void test_iterator_distance__vector_less(void** state);
void test_iterator_distance__vector_equal(void** state);
void test_iterator_distance__vector_greater(void** state);
void test_iterator_distance__deque_less(void** state);
void test_iterator_distance__deque_equal(void** state);
void test_iterator_distance__deque_greater(void** state);
void test_iterator_distance__list_less(void** state);
void test_iterator_distance__list_equal(void** state);
void test_iterator_distance__list_greater(void** state);
void test_iterator_distance__slist_less(void** state);
void test_iterator_distance__slist_equal(void** state);
void test_iterator_distance__slist_greater(void** state);
void test_iterator_distance__set_less(void** state);
void test_iterator_distance__set_equal(void** state);
void test_iterator_distance__set_greater(void** state);
void test_iterator_distance__multiset_less(void** state);
void test_iterator_distance__multiset_equal(void** state);
void test_iterator_distance__multiset_greater(void** state);
void test_iterator_distance__map_less(void** state);
void test_iterator_distance__map_equal(void** state);
void test_iterator_distance__map_greater(void** state);
void test_iterator_distance__multimap_less(void** state);
void test_iterator_distance__multimap_equal(void** state);
void test_iterator_distance__multimap_greater(void** state);
void test_iterator_distance__hash_set_less(void** state);
void test_iterator_distance__hash_set_equal(void** state);
void test_iterator_distance__hash_set_greater(void** state);
void test_iterator_distance__hash_multiset_less(void** state);
void test_iterator_distance__hash_multiset_equal(void** state);
void test_iterator_distance__hash_multiset_greater(void** state);
void test_iterator_distance__hash_map_less(void** state);
void test_iterator_distance__hash_map_equal(void** state);
void test_iterator_distance__hash_map_greater(void** state);
void test_iterator_distance__hash_multimap_less(void** state);
void test_iterator_distance__hash_multimap_equal(void** state);
void test_iterator_distance__hash_multimap_greater(void** state);
void test_iterator_distance__string_less(void** state);
void test_iterator_distance__string_equal(void** state);
void test_iterator_distance__string_greater(void** state);

/*
 * test iterator_advance
 */
UT_CASE_DECLARATION(iterator_advance)
void test_iterator_advance__invalid_iter(void** state);
void test_iterator_advance__vector_0(void** state);
void test_iterator_advance__vector_n(void** state);
void test_iterator_advance__vector_n_(void** state);
void test_iterator_advance__vector_end_n(void** state);
void test_iterator_advance__vector_prev_n(void** state);
void test_iterator_advance__deque_0(void** state);
void test_iterator_advance__deque_n(void** state);
void test_iterator_advance__deque_n_(void** state);
void test_iterator_advance__deque_end_n(void** state);
void test_iterator_advance__deque_prev_n(void** state);
void test_iterator_advance__list_0(void** state);
void test_iterator_advance__list_n(void** state);
void test_iterator_advance__list_n_(void** state);
void test_iterator_advance__list_end_n(void** state);
void test_iterator_advance__list_prev_n(void** state);
void test_iterator_advance__slist_0(void** state);
void test_iterator_advance__slist_n(void** state);
void test_iterator_advance__slist_n_(void** state);
void test_iterator_advance__slist_end_n(void** state);
void test_iterator_advance__slist_prev_n(void** state);
void test_iterator_advance__set_0(void** state);
void test_iterator_advance__set_n(void** state);
void test_iterator_advance__set_n_(void** state);
void test_iterator_advance__set_end_n(void** state);
void test_iterator_advance__set_prev_n(void** state);
void test_iterator_advance__multiset_0(void** state);
void test_iterator_advance__multiset_n(void** state);
void test_iterator_advance__multiset_n_(void** state);
void test_iterator_advance__multiset_end_n(void** state);
void test_iterator_advance__multiset_prev_n(void** state);
void test_iterator_advance__map_0(void** state);
void test_iterator_advance__map_n(void** state);
void test_iterator_advance__map_n_(void** state);
void test_iterator_advance__map_end_n(void** state);
void test_iterator_advance__map_prev_n(void** state);
void test_iterator_advance__multimap_0(void** state);
void test_iterator_advance__multimap_n(void** state);
void test_iterator_advance__multimap_n_(void** state);
void test_iterator_advance__multimap_end_n(void** state);
void test_iterator_advance__multimap_prev_n(void** state);
void test_iterator_advance__hash_set_0(void** state);
void test_iterator_advance__hash_set_n(void** state);
void test_iterator_advance__hash_set_n_(void** state);
void test_iterator_advance__hash_set_end_n(void** state);
void test_iterator_advance__hash_set_prev_n(void** state);
void test_iterator_advance__hash_multiset_0(void** state);
void test_iterator_advance__hash_multiset_n(void** state);
void test_iterator_advance__hash_multiset_n_(void** state);
void test_iterator_advance__hash_multiset_end_n(void** state);
void test_iterator_advance__hash_multiset_prev_n(void** state);
void test_iterator_advance__hash_map_0(void** state);
void test_iterator_advance__hash_map_n(void** state);
void test_iterator_advance__hash_map_n_(void** state);
void test_iterator_advance__hash_map_end_n(void** state);
void test_iterator_advance__hash_map_prev_n(void** state);
void test_iterator_advance__hash_multimap_0(void** state);
void test_iterator_advance__hash_multimap_n(void** state);
void test_iterator_advance__hash_multimap_n_(void** state);
void test_iterator_advance__hash_multimap_end_n(void** state);
void test_iterator_advance__hash_multimap_prev_n(void** state);
void test_iterator_advance__string_0(void** state);
void test_iterator_advance__string_n(void** state);
void test_iterator_advance__string_n_(void** state);
void test_iterator_advance__string_end_n(void** state);
void test_iterator_advance__string_prev_n(void** state);

#define UT_CSTL_ITERATOR_CASE\
    UT_SUIT_BEGIN(cstl_iterator, test_iterator_get_value__invalid_iter),\
    UT_CASE(test_iterator_get_value__null),\
    UT_CASE(test_iterator_get_value__vector),\
    UT_CASE(test_iterator_get_value__deque),\
    UT_CASE(test_iterator_get_value__list),\
    UT_CASE(test_iterator_get_value__slist),\
    UT_CASE(test_iterator_get_value__set),\
    UT_CASE(test_iterator_get_value__multiset),\
    UT_CASE(test_iterator_get_value__map),\
    UT_CASE(test_iterator_get_value__multimap),\
    UT_CASE(test_iterator_get_value__hash_set),\
    UT_CASE(test_iterator_get_value__hash_multiset),\
    UT_CASE(test_iterator_get_value__hash_map),\
    UT_CASE(test_iterator_get_value__hash_multimap),\
    UT_CASE(test_iterator_get_value__string),\
    UT_CASE_BEGIN(iterator_set_value, test_iterator_set_value__invalid_iter),\
    UT_CASE(test_iterator_set_value__null),\
    UT_CASE(test_iterator_set_value__vector),\
    UT_CASE(test_iterator_set_value__deque),\
    UT_CASE(test_iterator_set_value__list),\
    UT_CASE(test_iterator_set_value__slist),\
    UT_CASE(test_iterator_set_value__set),\
    UT_CASE(test_iterator_set_value__multiset),\
    UT_CASE(test_iterator_set_value__map),\
    UT_CASE(test_iterator_set_value__multimap),\
    UT_CASE(test_iterator_set_value__hash_set),\
    UT_CASE(test_iterator_set_value__hash_multiset),\
    UT_CASE(test_iterator_set_value__hash_map),\
    UT_CASE(test_iterator_set_value__hash_multimap),\
    UT_CASE(test_iterator_set_value__string),\
    UT_CASE_BEGIN(iterator_get_pointer, test_iterator_get_pointer__invalid_iter),\
    UT_CASE(test_iterator_get_pointer__vector),\
    UT_CASE(test_iterator_get_pointer__deque),\
    UT_CASE(test_iterator_get_pointer__list),\
    UT_CASE(test_iterator_get_pointer__slist),\
    UT_CASE(test_iterator_get_pointer__set),\
    UT_CASE(test_iterator_get_pointer__multiset),\
    UT_CASE(test_iterator_get_pointer__map),\
    UT_CASE(test_iterator_get_pointer__multimap),\
    UT_CASE(test_iterator_get_pointer__hash_set),\
    UT_CASE(test_iterator_get_pointer__hash_multiset),\
    UT_CASE(test_iterator_get_pointer__hash_map),\
    UT_CASE(test_iterator_get_pointer__hash_multimap),\
    UT_CASE(test_iterator_get_pointer__string),\
    UT_CASE_BEGIN(iterator_next, test_iterator_next__invalid_iter),\
    UT_CASE(test_iterator_next__vector),\
    UT_CASE(test_iterator_next__vector_end),\
    UT_CASE(test_iterator_next__deque),\
    UT_CASE(test_iterator_next__deque_end),\
    UT_CASE(test_iterator_next__list),\
    UT_CASE(test_iterator_next__list_end),\
    UT_CASE(test_iterator_next__slist),\
    UT_CASE(test_iterator_next__slist_end),\
    UT_CASE(test_iterator_next__set),\
    UT_CASE(test_iterator_next__set_end),\
    UT_CASE(test_iterator_next__multiset),\
    UT_CASE(test_iterator_next__multiset_end),\
    UT_CASE(test_iterator_next__map),\
    UT_CASE(test_iterator_next__map_end),\
    UT_CASE(test_iterator_next__multimap),\
    UT_CASE(test_iterator_next__multimap_end),\
    UT_CASE(test_iterator_next__hash_set),\
    UT_CASE(test_iterator_next__hash_set_end),\
    UT_CASE(test_iterator_next__hash_multiset),\
    UT_CASE(test_iterator_next__hash_multiset_end),\
    UT_CASE(test_iterator_next__hash_map),\
    UT_CASE(test_iterator_next__hash_map_end),\
    UT_CASE(test_iterator_next__hash_multimap),\
    UT_CASE(test_iterator_next__hash_multimap_end),\
    UT_CASE(test_iterator_next__string),\
    UT_CASE(test_iterator_next__string_end),\
    UT_CASE_BEGIN(iterator_prev, test_iterator_prev__invalid_iter),\
    UT_CASE(test_iterator_prev__vector),\
    UT_CASE(test_iterator_prev__vector_begin),\
    UT_CASE(test_iterator_prev__deque),\
    UT_CASE(test_iterator_prev__deque_begin),\
    UT_CASE(test_iterator_prev__list),\
    UT_CASE(test_iterator_prev__list_begin),\
    UT_CASE(test_iterator_prev__slist),\
    UT_CASE(test_iterator_prev__slist_begin),\
    UT_CASE(test_iterator_prev__set),\
    UT_CASE(test_iterator_prev__set_begin),\
    UT_CASE(test_iterator_prev__multiset),\
    UT_CASE(test_iterator_prev__multiset_begin),\
    UT_CASE(test_iterator_prev__map),\
    UT_CASE(test_iterator_prev__map_begin),\
    UT_CASE(test_iterator_prev__multimap),\
    UT_CASE(test_iterator_prev__multimap_begin),\
    UT_CASE(test_iterator_prev__hash_set),\
    UT_CASE(test_iterator_prev__hash_set_begin),\
    UT_CASE(test_iterator_prev__hash_multiset),\
    UT_CASE(test_iterator_prev__hash_multiset_begin),\
    UT_CASE(test_iterator_prev__hash_map),\
    UT_CASE(test_iterator_prev__hash_map_begin),\
    UT_CASE(test_iterator_prev__hash_multimap),\
    UT_CASE(test_iterator_prev__hash_multimap_begin),\
    UT_CASE(test_iterator_prev__string),\
    UT_CASE(test_iterator_prev__string_begin),\
    UT_CASE_BEGIN(iterator_next_n, test_iterator_next_n__invalid_iter),\
    UT_CASE(test_iterator_next_n__vector_0),\
    UT_CASE(test_iterator_next_n__vector_n),\
    UT_CASE(test_iterator_next_n__vector_n_),\
    UT_CASE(test_iterator_next_n__vector_end_n),\
    UT_CASE(test_iterator_next_n__vector_prev_n),\
    UT_CASE(test_iterator_next_n__deque_0),\
    UT_CASE(test_iterator_next_n__deque_n),\
    UT_CASE(test_iterator_next_n__deque_n_),\
    UT_CASE(test_iterator_next_n__deque_end_n),\
    UT_CASE(test_iterator_next_n__deque_prev_n),\
    UT_CASE(test_iterator_next_n__list),\
    UT_CASE(test_iterator_next_n__slist),\
    UT_CASE(test_iterator_next_n__set),\
    UT_CASE(test_iterator_next_n__multiset),\
    UT_CASE(test_iterator_next_n__map),\
    UT_CASE(test_iterator_next_n__multimap),\
    UT_CASE(test_iterator_next_n__hash_set),\
    UT_CASE(test_iterator_next_n__hash_multiset),\
    UT_CASE(test_iterator_next_n__hash_map),\
    UT_CASE(test_iterator_next_n__hash_multimap),\
    UT_CASE(test_iterator_next_n__string_0),\
    UT_CASE(test_iterator_next_n__string_n),\
    UT_CASE(test_iterator_next_n__string_n_),\
    UT_CASE(test_iterator_next_n__string_end_n),\
    UT_CASE(test_iterator_next_n__string_prev_n),\
    UT_CASE_BEGIN(iterator_prev_n, test_iterator_prev_n__invalid_iter),\
    UT_CASE(test_iterator_prev_n__vector_0),\
    UT_CASE(test_iterator_prev_n__vector_n),\
    UT_CASE(test_iterator_prev_n__vector_n_),\
    UT_CASE(test_iterator_prev_n__vector_end_n),\
    UT_CASE(test_iterator_prev_n__vector_prev_n),\
    UT_CASE(test_iterator_prev_n__deque_0),\
    UT_CASE(test_iterator_prev_n__deque_n),\
    UT_CASE(test_iterator_prev_n__deque_n_),\
    UT_CASE(test_iterator_prev_n__deque_end_n),\
    UT_CASE(test_iterator_prev_n__deque_prev_n),\
    UT_CASE(test_iterator_prev_n__list),\
    UT_CASE(test_iterator_prev_n__slist),\
    UT_CASE(test_iterator_prev_n__set),\
    UT_CASE(test_iterator_prev_n__multiset),\
    UT_CASE(test_iterator_prev_n__map),\
    UT_CASE(test_iterator_prev_n__multimap),\
    UT_CASE(test_iterator_prev_n__hash_set),\
    UT_CASE(test_iterator_prev_n__hash_multiset),\
    UT_CASE(test_iterator_prev_n__hash_map),\
    UT_CASE(test_iterator_prev_n__hash_multimap),\
    UT_CASE(test_iterator_prev_n__string_0),\
    UT_CASE(test_iterator_prev_n__string_n),\
    UT_CASE(test_iterator_prev_n__string_n_),\
    UT_CASE(test_iterator_prev_n__string_end_n),\
    UT_CASE(test_iterator_prev_n__string_prev_n),\
    UT_CASE_BEGIN(iterator_equal, test_iterator_equal__invalid_first),\
    UT_CASE(test_iterator_equal__invalid_second),\
    UT_CASE(test_iterator_equal__vector_equal),\
    UT_CASE(test_iterator_equal__vector_not_equal),\
    UT_CASE(test_iterator_equal__deque_equal),\
    UT_CASE(test_iterator_equal__deque_not_equal),\
    UT_CASE(test_iterator_equal__list_equal),\
    UT_CASE(test_iterator_equal__list_not_equal),\
    UT_CASE(test_iterator_equal__slist_equal),\
    UT_CASE(test_iterator_equal__slist_not_equal),\
    UT_CASE(test_iterator_equal__set_equal),\
    UT_CASE(test_iterator_equal__set_not_equal),\
    UT_CASE(test_iterator_equal__multiset_equal),\
    UT_CASE(test_iterator_equal__multiset_not_equal),\
    UT_CASE(test_iterator_equal__map_equal),\
    UT_CASE(test_iterator_equal__map_not_equal),\
    UT_CASE(test_iterator_equal__multimap_equal),\
    UT_CASE(test_iterator_equal__multimap_not_equal),\
    UT_CASE(test_iterator_equal__hash_set_equal),\
    UT_CASE(test_iterator_equal__hash_set_not_equal),\
    UT_CASE(test_iterator_equal__hash_multiset_equal),\
    UT_CASE(test_iterator_equal__hash_multiset_not_equal),\
    UT_CASE(test_iterator_equal__hash_map_equal),\
    UT_CASE(test_iterator_equal__hash_map_not_equal),\
    UT_CASE(test_iterator_equal__hash_multimap_equal),\
    UT_CASE(test_iterator_equal__hash_multimap_not_equal),\
    UT_CASE(test_iterator_equal__string_equal),\
    UT_CASE(test_iterator_equal__string_not_equal),\
    UT_CASE_BEGIN(iterator_not_equal, test_iterator_not_equal__invalid_first),\
    UT_CASE(test_iterator_not_equal__invalid_second),\
    UT_CASE(test_iterator_not_equal__vector_equal),\
    UT_CASE(test_iterator_not_equal__vector_not_equal),\
    UT_CASE(test_iterator_not_equal__deque_equal),\
    UT_CASE(test_iterator_not_equal__deque_not_equal),\
    UT_CASE(test_iterator_not_equal__list_equal),\
    UT_CASE(test_iterator_not_equal__list_not_equal),\
    UT_CASE(test_iterator_not_equal__slist_equal),\
    UT_CASE(test_iterator_not_equal__slist_not_equal),\
    UT_CASE(test_iterator_not_equal__set_equal),\
    UT_CASE(test_iterator_not_equal__set_not_equal),\
    UT_CASE(test_iterator_not_equal__multiset_equal),\
    UT_CASE(test_iterator_not_equal__multiset_not_equal),\
    UT_CASE(test_iterator_not_equal__map_equal),\
    UT_CASE(test_iterator_not_equal__map_not_equal),\
    UT_CASE(test_iterator_not_equal__multimap_equal),\
    UT_CASE(test_iterator_not_equal__multimap_not_equal),\
    UT_CASE(test_iterator_not_equal__hash_set_equal),\
    UT_CASE(test_iterator_not_equal__hash_set_not_equal),\
    UT_CASE(test_iterator_not_equal__hash_multiset_equal),\
    UT_CASE(test_iterator_not_equal__hash_multiset_not_equal),\
    UT_CASE(test_iterator_not_equal__hash_map_equal),\
    UT_CASE(test_iterator_not_equal__hash_map_not_equal),\
    UT_CASE(test_iterator_not_equal__hash_multimap_equal),\
    UT_CASE(test_iterator_not_equal__hash_multimap_not_equal),\
    UT_CASE(test_iterator_not_equal__string_equal),\
    UT_CASE(test_iterator_not_equal__string_not_equal),\
    UT_CASE_BEGIN(iterator_less, test_iterator_less__invalid_first),\
    UT_CASE(test_iterator_less__invalid_second),\
    UT_CASE(test_iterator_less__vector_less),\
    UT_CASE(test_iterator_less__vector_equal),\
    UT_CASE(test_iterator_less__vector_greater),\
    UT_CASE(test_iterator_less__deque_less),\
    UT_CASE(test_iterator_less__deque_equal),\
    UT_CASE(test_iterator_less__deque_greater),\
    UT_CASE(test_iterator_less__list),\
    UT_CASE(test_iterator_less__slist),\
    UT_CASE(test_iterator_less__set),\
    UT_CASE(test_iterator_less__multiset),\
    UT_CASE(test_iterator_less__map),\
    UT_CASE(test_iterator_less__multimap),\
    UT_CASE(test_iterator_less__hash_set),\
    UT_CASE(test_iterator_less__hash_multiset),\
    UT_CASE(test_iterator_less__hash_map),\
    UT_CASE(test_iterator_less__hash_multimap),\
    UT_CASE(test_iterator_less__string_less),\
    UT_CASE(test_iterator_less__string_equal),\
    UT_CASE(test_iterator_less__string_greater),\
    UT_CASE_BEGIN(iterator_less_equal, test_iterator_less_equal__invalid_first),\
    UT_CASE(test_iterator_less_equal__invalid_second),\
    UT_CASE(test_iterator_less_equal__vector_less),\
    UT_CASE(test_iterator_less_equal__vector_equal),\
    UT_CASE(test_iterator_less_equal__vector_greater),\
    UT_CASE(test_iterator_less_equal__deque_less),\
    UT_CASE(test_iterator_less_equal__deque_equal),\
    UT_CASE(test_iterator_less_equal__deque_greater),\
    UT_CASE(test_iterator_less_equal__list),\
    UT_CASE(test_iterator_less_equal__slist),\
    UT_CASE(test_iterator_less_equal__set),\
    UT_CASE(test_iterator_less_equal__multiset),\
    UT_CASE(test_iterator_less_equal__map),\
    UT_CASE(test_iterator_less_equal__multimap),\
    UT_CASE(test_iterator_less_equal__hash_set),\
    UT_CASE(test_iterator_less_equal__hash_multiset),\
    UT_CASE(test_iterator_less_equal__hash_map),\
    UT_CASE(test_iterator_less_equal__hash_multimap),\
    UT_CASE(test_iterator_less_equal__string_less),\
    UT_CASE(test_iterator_less_equal__string_equal),\
    UT_CASE(test_iterator_less_equal__string_greater),\
    UT_CASE_BEGIN(iterator_greater, test_iterator_greater__invalid_first),\
    UT_CASE(test_iterator_greater__invalid_second),\
    UT_CASE(test_iterator_greater__vector_less),\
    UT_CASE(test_iterator_greater__vector_equal),\
    UT_CASE(test_iterator_greater__vector_greater),\
    UT_CASE(test_iterator_greater__deque_less),\
    UT_CASE(test_iterator_greater__deque_equal),\
    UT_CASE(test_iterator_greater__deque_greater),\
    UT_CASE(test_iterator_greater__list),\
    UT_CASE(test_iterator_greater__slist),\
    UT_CASE(test_iterator_greater__set),\
    UT_CASE(test_iterator_greater__multiset),\
    UT_CASE(test_iterator_greater__map),\
    UT_CASE(test_iterator_greater__multimap),\
    UT_CASE(test_iterator_greater__hash_set),\
    UT_CASE(test_iterator_greater__hash_multiset),\
    UT_CASE(test_iterator_greater__hash_map),\
    UT_CASE(test_iterator_greater__hash_multimap),\
    UT_CASE(test_iterator_greater__string_less),\
    UT_CASE(test_iterator_greater__string_equal),\
    UT_CASE(test_iterator_greater__string_greater),\
    UT_CASE_BEGIN(iterator_greater_equal, test_iterator_greater_equal__invalid_first),\
    UT_CASE(test_iterator_greater_equal__invalid_second),\
    UT_CASE(test_iterator_greater_equal__vector_less),\
    UT_CASE(test_iterator_greater_equal__vector_equal),\
    UT_CASE(test_iterator_greater_equal__vector_greater),\
    UT_CASE(test_iterator_greater_equal__deque_less),\
    UT_CASE(test_iterator_greater_equal__deque_equal),\
    UT_CASE(test_iterator_greater_equal__deque_greater),\
    UT_CASE(test_iterator_greater_equal__list),\
    UT_CASE(test_iterator_greater_equal__slist),\
    UT_CASE(test_iterator_greater_equal__set),\
    UT_CASE(test_iterator_greater_equal__multiset),\
    UT_CASE(test_iterator_greater_equal__map),\
    UT_CASE(test_iterator_greater_equal__multimap),\
    UT_CASE(test_iterator_greater_equal__hash_set),\
    UT_CASE(test_iterator_greater_equal__hash_multiset),\
    UT_CASE(test_iterator_greater_equal__hash_map),\
    UT_CASE(test_iterator_greater_equal__hash_multimap),\
    UT_CASE(test_iterator_greater_equal__string_less),\
    UT_CASE(test_iterator_greater_equal__string_equal),\
    UT_CASE(test_iterator_greater_equal__string_greater),\
    UT_CASE_BEGIN(iterator_at, test_iterator_at__invalid_iter),\
    UT_CASE(test_iterator_at__vector_0),\
    UT_CASE(test_iterator_at__vector_n),\
    UT_CASE(test_iterator_at__vector_n_),\
    UT_CASE(test_iterator_at__vector_end_n),\
    UT_CASE(test_iterator_at__vector_prev_n),\
    UT_CASE(test_iterator_at__deque_0),\
    UT_CASE(test_iterator_at__deque_n),\
    UT_CASE(test_iterator_at__deque_n_),\
    UT_CASE(test_iterator_at__deque_end_n),\
    UT_CASE(test_iterator_at__deque_prev_n),\
    UT_CASE(test_iterator_at__list),\
    UT_CASE(test_iterator_at__slist),\
    UT_CASE(test_iterator_at__set),\
    UT_CASE(test_iterator_at__multiset),\
    UT_CASE(test_iterator_at__map),\
    UT_CASE(test_iterator_at__multimap),\
    UT_CASE(test_iterator_at__hash_set),\
    UT_CASE(test_iterator_at__hash_multiset),\
    UT_CASE(test_iterator_at__hash_map),\
    UT_CASE(test_iterator_at__hash_multimap),\
    UT_CASE(test_iterator_at__string_0),\
    UT_CASE(test_iterator_at__string_n),\
    UT_CASE(test_iterator_at__string_n_),\
    UT_CASE(test_iterator_at__string_end_n),\
    UT_CASE(test_iterator_at__string_prev_n),\
    UT_CASE_BEGIN(iterator_minus, test_iterator_minus__invalid_first),\
    UT_CASE(test_iterator_minus__invalid_second),\
    UT_CASE(test_iterator_minus__not_same_container),\
    UT_CASE(test_iterator_minus__vector_less),\
    UT_CASE(test_iterator_minus__vector_equal),\
    UT_CASE(test_iterator_minus__vector_greater),\
    UT_CASE(test_iterator_minus__deque_less),\
    UT_CASE(test_iterator_minus__deque_equal),\
    UT_CASE(test_iterator_minus__deque_greater),\
    UT_CASE(test_iterator_minus__list),\
    UT_CASE(test_iterator_minus__slist),\
    UT_CASE(test_iterator_minus__set),\
    UT_CASE(test_iterator_minus__multiset),\
    UT_CASE(test_iterator_minus__map),\
    UT_CASE(test_iterator_minus__multimap),\
    UT_CASE(test_iterator_minus__hash_set),\
    UT_CASE(test_iterator_minus__hash_multiset),\
    UT_CASE(test_iterator_minus__hash_map),\
    UT_CASE(test_iterator_minus__hash_multimap),\
    UT_CASE(test_iterator_minus__string_less),\
    UT_CASE(test_iterator_minus__string_equal),\
    UT_CASE(test_iterator_minus__string_greater),\
    UT_CASE_BEGIN(iterator_distance, test_iterator_distance__invalid_first),\
    UT_CASE(test_iterator_distance__invalid_second),\
    UT_CASE(test_iterator_distance__not_same_container),\
    UT_CASE(test_iterator_distance__vector_less),\
    UT_CASE(test_iterator_distance__vector_equal),\
    UT_CASE(test_iterator_distance__vector_greater),\
    UT_CASE(test_iterator_distance__deque_less),\
    UT_CASE(test_iterator_distance__deque_equal),\
    UT_CASE(test_iterator_distance__deque_greater),\
    UT_CASE(test_iterator_distance__list_less),\
    UT_CASE(test_iterator_distance__list_equal),\
    UT_CASE(test_iterator_distance__list_greater),\
    UT_CASE(test_iterator_distance__slist_less),\
    UT_CASE(test_iterator_distance__slist_equal),\
    UT_CASE(test_iterator_distance__slist_greater),\
    UT_CASE(test_iterator_distance__set_less),\
    UT_CASE(test_iterator_distance__set_equal),\
    UT_CASE(test_iterator_distance__set_greater),\
    UT_CASE(test_iterator_distance__multiset_less),\
    UT_CASE(test_iterator_distance__multiset_equal),\
    UT_CASE(test_iterator_distance__multiset_greater),\
    UT_CASE(test_iterator_distance__map_less),\
    UT_CASE(test_iterator_distance__map_equal),\
    UT_CASE(test_iterator_distance__map_greater),\
    UT_CASE(test_iterator_distance__multimap_less),\
    UT_CASE(test_iterator_distance__multimap_equal),\
    UT_CASE(test_iterator_distance__multimap_greater),\
    UT_CASE(test_iterator_distance__hash_set_less),\
    UT_CASE(test_iterator_distance__hash_set_equal),\
    UT_CASE(test_iterator_distance__hash_set_greater),\
    UT_CASE(test_iterator_distance__hash_multiset_less),\
    UT_CASE(test_iterator_distance__hash_multiset_equal),\
    UT_CASE(test_iterator_distance__hash_multiset_greater),\
    UT_CASE(test_iterator_distance__hash_map_less),\
    UT_CASE(test_iterator_distance__hash_map_equal),\
    UT_CASE(test_iterator_distance__hash_map_greater),\
    UT_CASE(test_iterator_distance__hash_multimap_less),\
    UT_CASE(test_iterator_distance__hash_multimap_equal),\
    UT_CASE(test_iterator_distance__hash_multimap_greater),\
    UT_CASE(test_iterator_distance__string_less),\
    UT_CASE(test_iterator_distance__string_equal),\
    UT_CASE(test_iterator_distance__string_greater),\
    UT_CASE_BEGIN(iterator_advance, test_iterator_advance__invalid_iter),\
    UT_CASE(test_iterator_advance__vector_0),\
    UT_CASE(test_iterator_advance__vector_n),\
    UT_CASE(test_iterator_advance__vector_n_),\
    UT_CASE(test_iterator_advance__vector_end_n),\
    UT_CASE(test_iterator_advance__vector_prev_n),\
    UT_CASE(test_iterator_advance__deque_0),\
    UT_CASE(test_iterator_advance__deque_n),\
    UT_CASE(test_iterator_advance__deque_n_),\
    UT_CASE(test_iterator_advance__deque_end_n),\
    UT_CASE(test_iterator_advance__deque_prev_n),\
    UT_CASE(test_iterator_advance__list_0),\
    UT_CASE(test_iterator_advance__list_n),\
    UT_CASE(test_iterator_advance__list_n_),\
    UT_CASE(test_iterator_advance__list_end_n),\
    UT_CASE(test_iterator_advance__list_prev_n),\
    UT_CASE(test_iterator_advance__slist_0),\
    UT_CASE(test_iterator_advance__slist_n),\
    UT_CASE(test_iterator_advance__slist_n_),\
    UT_CASE(test_iterator_advance__slist_end_n),\
    UT_CASE(test_iterator_advance__slist_prev_n),\
    UT_CASE(test_iterator_advance__set_0),\
    UT_CASE(test_iterator_advance__set_n),\
    UT_CASE(test_iterator_advance__set_n_),\
    UT_CASE(test_iterator_advance__set_end_n),\
    UT_CASE(test_iterator_advance__set_prev_n),\
    UT_CASE(test_iterator_advance__multiset_0),\
    UT_CASE(test_iterator_advance__multiset_n),\
    UT_CASE(test_iterator_advance__multiset_n_),\
    UT_CASE(test_iterator_advance__multiset_end_n),\
    UT_CASE(test_iterator_advance__multiset_prev_n),\
    UT_CASE(test_iterator_advance__map_0),\
    UT_CASE(test_iterator_advance__map_n),\
    UT_CASE(test_iterator_advance__map_n_),\
    UT_CASE(test_iterator_advance__map_end_n),\
    UT_CASE(test_iterator_advance__map_prev_n),\
    UT_CASE(test_iterator_advance__multimap_0),\
    UT_CASE(test_iterator_advance__multimap_n),\
    UT_CASE(test_iterator_advance__multimap_n_),\
    UT_CASE(test_iterator_advance__multimap_end_n),\
    UT_CASE(test_iterator_advance__multimap_prev_n),\
    UT_CASE(test_iterator_advance__hash_set_0),\
    UT_CASE(test_iterator_advance__hash_set_n),\
    UT_CASE(test_iterator_advance__hash_set_n_),\
    UT_CASE(test_iterator_advance__hash_set_end_n),\
    UT_CASE(test_iterator_advance__hash_set_prev_n),\
    UT_CASE(test_iterator_advance__hash_multiset_0),\
    UT_CASE(test_iterator_advance__hash_multiset_n),\
    UT_CASE(test_iterator_advance__hash_multiset_n_),\
    UT_CASE(test_iterator_advance__hash_multiset_end_n),\
    UT_CASE(test_iterator_advance__hash_multiset_prev_n),\
    UT_CASE(test_iterator_advance__hash_map_0),\
    UT_CASE(test_iterator_advance__hash_map_n),\
    UT_CASE(test_iterator_advance__hash_map_n_),\
    UT_CASE(test_iterator_advance__hash_map_end_n),\
    UT_CASE(test_iterator_advance__hash_map_prev_n),\
    UT_CASE(test_iterator_advance__hash_multimap_0),\
    UT_CASE(test_iterator_advance__hash_multimap_n),\
    UT_CASE(test_iterator_advance__hash_multimap_n_),\
    UT_CASE(test_iterator_advance__hash_multimap_end_n),\
    UT_CASE(test_iterator_advance__hash_multimap_prev_n),\
    UT_CASE(test_iterator_advance__string_0),\
    UT_CASE(test_iterator_advance__string_n),\
    UT_CASE(test_iterator_advance__string_n_),\
    UT_CASE(test_iterator_advance__string_end_n),\
    UT_CASE(test_iterator_advance__string_prev_n)

#endif /* _UT_CSTL_ITERATOR_H_ */

