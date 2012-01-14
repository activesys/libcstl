/*
 *  The interface of set iterator.
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

#ifndef _CSTL_SET_ITERATOR_H_
#define _CSTL_SET_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t set_iterator_t;
typedef iterator_t set_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create set iterator.
 * @return set iterator.
 * @remarks the returned iterator is invalid iterator.
 */
extern set_iterator_t create_set_iterator(void);

/**
 * Get data value referenced by iterator.
 * @param it_iter    set iterator.
 * @param pv_value   data value buffer.
 * @return void.
 * @remarks it_iter must be valid set iterator, otherwise the behavior is undefined. if pv_value == NULL, then the
 *          behavior is undefined.
 */
extern void _set_iterator_get_value(set_iterator_t it_iter, void* pv_value);

/**
 * Get data value pointer referenced by iterator.
 * @param it_iter    set iterator.
 * @return void.
 * @remarks it_iter must be valid set iterator, otherwise the behavior is undefined.
 */
extern const void* _set_iterator_get_pointer(set_iterator_t it_iter);

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 * @param it_iter    set iterator.
 * @return void.
 * @remarks it_iter must be valid set iterator, otherwise the behavior is undefined.
 */
extern const void* _set_iterator_get_pointer_ignore_cstr(set_iterator_t it_iter);

/**
 * Return iterator reference next element.
 * @param  it_iter    current iterator.
 * @return next iterator.
 * @remarks it_iter and next iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern set_iterator_t _set_iterator_next(set_iterator_t it_iter);

/**
 * Return iterator reference previous element.
 * @param  it_iter    current iterator.
 * @return previous iterator.
 * @remarks it_iter and previous iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern set_iterator_t _set_iterator_prev(set_iterator_t it_iter);

/**
 * Test the two set iterator are equal.
 * @param it_first    set iterator.
 * @param it_second   set iterator.
 * @return true, if the two iterator are equal, else return false.
 * @remarks the two iterator must be valid set iterator, otherwise the behavior is undefined.
 */
extern bool_t _set_iterator_equal(set_iterator_t it_first, set_iterator_t it_second);

/**
 * Calculate distance between two iterators.
 * @param it_first    set iterator.
 * @param it_second   set iterator.
 * @return distance.
 * @remarks the two iterator must be valid set iterator, and must be belong to same set, otherwise the behavior
 *          is undefined. the result distance may be less than 0, equal to 0 or greater than 0.
 */
extern int _set_iterator_distance(set_iterator_t it_first, set_iterator_t it_second);

/**
 * Test the first iterator is before the second.
 * @param it_first    set iterator.
 * @param it_second   set iterator.
 * @return true, if the first iterator is before the second, else return false.
 * @remarks the two iterator must be valid set iterator, and must be belong to same set, otherwise the behavior
 *          is undefined.
 */
extern bool_t _set_iterator_before(set_iterator_t it_first, set_iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_SET_ITERATOR_H_ */
/** eof **/

