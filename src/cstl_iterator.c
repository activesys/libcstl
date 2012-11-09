/*
 *  The implement of iterator module.
 *  Copyright (C)  2008 - 2012  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Get value that pointed by iterator.
 */
void iterator_get_value(iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _INPUT_ITERATOR));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            _vector_iterator_get_value(it_iter, pv_value);
            break;
        case _LIST_CONTAINER:
            _list_iterator_get_value(it_iter, pv_value);
            break;
        case _DEQUE_CONTAINER:
            _deque_iterator_get_value(it_iter, pv_value);
            break;
        case _SLIST_CONTAINER:
            _slist_iterator_get_value(it_iter, pv_value);
            break;
        case _SET_CONTAINER:
            _set_iterator_get_value(it_iter, pv_value);
            break;
        case _MULTISET_CONTAINER:
            _multiset_iterator_get_value(it_iter, pv_value);
            break;
        case _MAP_CONTAINER:
            _map_iterator_get_value(it_iter, pv_value);
            break;
        case _MULTIMAP_CONTAINER:
            _multimap_iterator_get_value(it_iter, pv_value);
            break;
        case _HASH_SET_CONTAINER:
            _hash_set_iterator_get_value(it_iter, pv_value);
            break;
        case _HASH_MULTISET_CONTAINER:
            _hash_multiset_iterator_get_value(it_iter, pv_value);
            break;
        case _HASH_MAP_CONTAINER:
            _hash_map_iterator_get_value(it_iter, pv_value);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            _hash_multimap_iterator_get_value(it_iter, pv_value);
            break;
        case _BASIC_STRING_CONTAINER:
            _basic_string_iterator_get_value(it_iter, pv_value);
            break;
        default:
            assert(false);
            break;
    }
}

/**
 * Set value that pointed by iterator.
 */
void iterator_set_value(iterator_t it_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _OUTPUT_ITERATOR));
 
    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            _vector_iterator_set_value(it_iter, cpv_value);
            break;
        case _LIST_CONTAINER:
            _list_iterator_set_value(it_iter, cpv_value);
            break;
        case _DEQUE_CONTAINER:
            _deque_iterator_set_value(it_iter, cpv_value);
            break;
        case _SLIST_CONTAINER:
            _slist_iterator_set_value(it_iter, cpv_value);
            break;
        case _BASIC_STRING_CONTAINER:
            _basic_string_iterator_set_value(it_iter, cpv_value);
            break;
        default:
            assert(false);
            break;
    }
}

/**
 * Get pointer that pointed by iterator.
 */
const void* iterator_get_pointer(iterator_t it_iter)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _INPUT_ITERATOR));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_get_pointer(it_iter);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_get_pointer(it_iter);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_get_pointer(it_iter);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_get_pointer(it_iter);
            break;
        case _SET_CONTAINER:
            return _set_iterator_get_pointer(it_iter);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_get_pointer(it_iter);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_get_pointer(it_iter);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_get_pointer(it_iter);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_get_pointer(it_iter);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_get_pointer(it_iter);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_get_pointer(it_iter);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_get_pointer(it_iter);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_get_pointer(it_iter);
            break;
        default:
            assert(false);
            return NULL;
            break;
    }
}

/**
 * Move iterator to next position.
 */
iterator_t iterator_next(iterator_t it_iter)
{
    assert(_iterator_is_valid(it_iter));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_next(it_iter);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_next(it_iter);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_next(it_iter);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_next(it_iter);
            break;
        case _SET_CONTAINER:
            return _set_iterator_next(it_iter);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_next(it_iter);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_next(it_iter);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_next(it_iter);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_next(it_iter);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_next(it_iter);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_next(it_iter);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_next(it_iter);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_next(it_iter);
            break;
        default:
            assert(false);
            return it_iter;
            break;
    }
}

/**
 * Move iterator to previous position.
 */
iterator_t iterator_prev(iterator_t it_iter)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _BIDIRECTIONAL_ITERATOR));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_prev(it_iter);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_prev(it_iter);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_prev(it_iter);
            break;
        case _SET_CONTAINER:
            return _set_iterator_prev(it_iter);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_prev(it_iter);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_prev(it_iter);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_prev(it_iter);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_prev(it_iter);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_prev(it_iter);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_prev(it_iter);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_prev(it_iter);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_prev(it_iter);
            break;
        default:
            assert(false);
            return it_iter;
            break;
    }
}

/**
 * Move iterator to next n position.
 */
iterator_t iterator_next_n(iterator_t it_iter, int n_step)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));

    if (n_step == 0) {
        return it_iter;
    }

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_next_n(it_iter, n_step);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_next_n(it_iter, n_step);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_next_n(it_iter, n_step);
            break;
        default:
            assert(false);
            return it_iter;
            break;
    }
}

/**
 * Move iterator to prev n position.
 */
iterator_t iterator_prev_n(iterator_t it_iter, int n_step)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));

    if (n_step == 0) {
        return it_iter;
    }

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_prev_n(it_iter, n_step);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_prev_n(it_iter, n_step);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_prev_n(it_iter, n_step);
            break;
        default:
            assert(false);
            return it_iter;
            break;
    }
}

/**
 * Test two iterator are equal or not.
 */
bool_t iterator_equal(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_is_valid(it_first));
    assert(_iterator_is_valid(it_second));
    assert(_iterator_limit_type(it_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_second, _INPUT_ITERATOR));

    if (it_first._t_containertype != it_second._t_containertype) {
        return false;
    }

    switch (it_first._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_equal(it_first, it_second);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_equal(it_first, it_second);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_equal(it_first, it_second);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_equal(it_first, it_second);
            break;
        case _SET_CONTAINER:
            return _set_iterator_equal(it_first, it_second);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_equal(it_first, it_second);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_equal(it_first, it_second);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_equal(it_first, it_second);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_equal(it_first, it_second);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_equal(it_first, it_second);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_equal(it_first, it_second);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_equal(it_first, it_second);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_equal(it_first, it_second);
            break;
        default:
            assert(false);
            return false;
            break;
    }
}

/**
 * Test two iterator are equal or not.
 */
bool_t iterator_not_equal(iterator_t it_first, iterator_t it_second)
{
    return !iterator_equal(it_first, it_second);
}

/**
 * Test first iterator is less than second iterator.
 */
bool_t iterator_less(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_is_valid(it_first));
    assert(_iterator_is_valid(it_second));
    assert(_iterator_limit_type(it_first, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_limit_type(it_second, _RANDOM_ACCESS_ITERATOR));

    switch (it_first._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_less(it_first, it_second);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_less(it_first, it_second);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_less(it_first, it_second);
            break;
        default:
            assert(false);
            return false;
            break;
    }
}

/**
 * Test first iterator is less than or equal to second iterator.
 */
bool_t iterator_less_equal(iterator_t it_first, iterator_t it_second)
{
    if (iterator_less(it_first, it_second) || iterator_equal(it_first, it_second)) {
        return true;
    } else {
        return false;
    }
}


/**
 * Test first iterator is greater than second iterator.
 */
bool_t iterator_greater(iterator_t it_first, iterator_t it_second)
{
    return iterator_less(it_second, it_first);
}

/**
 * Test first iterator is greater than or equal to second iterator.
 */
bool_t iterator_greater_equal(iterator_t it_first, iterator_t it_second)
{
    if (iterator_greater(it_first, it_second) || iterator_equal(it_first, it_second)) {
        return true;
    } else {
        return false;
    }
}

/**
 * Element random access.
 */
void* iterator_at(iterator_t it_iter, int n_index)
{
    assert(_iterator_is_valid(it_iter));
    assert(_iterator_limit_type(it_iter, _RANDOM_ACCESS_ITERATOR));

    switch (it_iter._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_at(it_iter, n_index);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_at(it_iter, n_index);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_at(it_iter, n_index);
            break;
        default:
            assert(false);
            return NULL;
            break;
    }
}

/**
 * Iterator distance.
 */
int iterator_minus(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_is_valid(it_first));
    assert(_iterator_is_valid(it_second));
    assert(_iterator_limit_type(it_first, _RANDOM_ACCESS_ITERATOR));

    switch (it_first._t_containertype) {
        case _VECTOR_CONTAINER:
            return _vector_iterator_minus(it_first, it_second);
            break;
        case _DEQUE_CONTAINER:
            return _deque_iterator_minus(it_first, it_second);
            break;
        case _BASIC_STRING_CONTAINER:
            return _basic_string_iterator_minus(it_first, it_second);
            break;
        default:
            assert(false);
            return 0;
            break;
    }
}

/**
 * Iterator next n for all iterator type.
 */
iterator_t iterator_advance(iterator_t it_iter, int n_step)
{
    int i = 0;

    if (n_step > 0 ||
        (it_iter._t_iteratortype != _RANDOM_ACCESS_ITERATOR &&
         it_iter._t_iteratortype != _BIDIRECTIONAL_ITERATOR)) {
        for (i = 0; i < abs(n_step); ++i) {
            it_iter = iterator_next(it_iter);
        }
    } else {
        for (i = 0; i < abs(n_step); ++i) {
            it_iter = iterator_prev(it_iter);
        }
    }

    return it_iter;
}

/**
 * Iterator distance for all iterator type.
 */
int iterator_distance(iterator_t it_first, iterator_t it_second)
{
    assert(_iterator_is_valid(it_first));
    assert(_iterator_is_valid(it_second));
    assert(_iterator_same_type(it_first, it_second));

    switch (it_first._t_containertype) {
        case _VECTOR_CONTAINER:
        case _DEQUE_CONTAINER:
        case _BASIC_STRING_CONTAINER:
            return iterator_minus(it_second, it_first);
            break;
        case _LIST_CONTAINER:
            return _list_iterator_distance(it_first, it_second);
            break;
        case _SLIST_CONTAINER:
            return _slist_iterator_distance(it_first, it_second);
            break;
        case _SET_CONTAINER:
            return _set_iterator_distance(it_first, it_second);
            break;
        case _MULTISET_CONTAINER:
            return _multiset_iterator_distance(it_first, it_second);
            break;
        case _MAP_CONTAINER:
            return _map_iterator_distance(it_first, it_second);
            break;
        case _MULTIMAP_CONTAINER:
            return _multimap_iterator_distance(it_first, it_second);
            break;
        case _HASH_SET_CONTAINER:
            return _hash_set_iterator_distance(it_first, it_second);
            break;
        case _HASH_MULTISET_CONTAINER:
            return _hash_multiset_iterator_distance(it_first, it_second);
            break;
        case _HASH_MAP_CONTAINER:
            return _hash_map_iterator_distance(it_first, it_second);
            break;
        case _HASH_MULTIMAP_CONTAINER:
            return _hash_multimap_iterator_distance(it_first, it_second);
            break;
        default:
            assert(false);
            return 0;
            break;
    }
}

/** local function implementation section **/

/** eof **/

