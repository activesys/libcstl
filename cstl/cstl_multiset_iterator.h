/*
 *  The iterator interface of multiset.
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

#ifndef _CSTL_MULTISET_ITERATOR_H_
#define _CSTL_MULTISET_ITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t multiset_iterator_t;
typedef iterator_t multiset_reverse_iterator_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create multiset iterator.
 * @return multiset iterator.
 * @remarks the returned iterator is invalid iterator.
 */
extern multiset_iterator_t create_multiset_iterator(void);

/**
 * Get data value referenced by iterator.
 * @param it_iter    multiset iterator.
 * @param pv_value   data value buffer.
 * @return void.
 * @remarks it_iter must be valid multiset iterator, otherwise the behavior is undefined. if pv_value == NULL, then the
 *          behavior is undefined.
 */
extern void _multiset_iterator_get_value(multiset_iterator_t it_iter, void* pv_value);

/**
 * Get data value pointer referenced by iterator.
 * @param it_iter    multiset iterator.
 * @return void.
 * @remarks it_iter must be valid multiset iterator, otherwise the behavior is undefined.
 */
extern const void* _multiset_iterator_get_pointer(multiset_iterator_t it_iter);

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 * @param it_iter    multiset iterator.
 * @return void.
 * @remarks it_iter must be valid multiset iterator, otherwise the behavior is undefined.
 */
extern const void* _multiset_iterator_get_pointer_ignore_cstr(multiset_iterator_t it_iter);

/**
 * Return iterator reference next element.
 * @param  it_iter    current iterator.
 * @return next iterator.
 * @remarks it_iter and next iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_iterator_next(multiset_iterator_t it_iter);

/**
 * Return iterator reference previous element.
 * @param  it_iter    current iterator.
 * @return previous iterator.
 * @remarks it_iter and previous iterator must be valid iterator, otherwise the behavior is undefined.
 */
extern multiset_iterator_t _multiset_iterator_prev(multiset_iterator_t it_iter);

/**
 * Test the two multiset iterator are equal.
 * @param it_first    multiset iterator.
 * @param it_second   multiset iterator.
 * @return true, if the two iterator are equal, else return false.
 * @remarks the two iterator must be valid multiset iterator, otherwise the behavior is undefined.
 */
extern bool_t _multiset_iterator_equal(multiset_iterator_t it_first, multiset_iterator_t it_second);

/**
 * Calculate distance between two iterators.
 * @param it_first    multiset iterator.
 * @param it_second   multiset iterator.
 * @return distance.
 * @remarks the two iterator must be valid multiset iterator, and must be belong to same multiset, otherwise the behavior
 *          is undefined. the result distance may be less than 0, equal to 0 or greater than 0.
 */
extern int _multiset_iterator_distance(multiset_iterator_t it_first, multiset_iterator_t it_second);

/**
 * Test the first iterator is before the second.
 * @param it_first    multiset iterator.
 * @param it_second   multiset iterator.
 * @return true, if the first iterator is before the second, else return false.
 * @remarks the two iterator must be valid multiset iterator, and must be belong to same multiset, otherwise the behavior
 *          is undefined.
 */
extern bool_t _multiset_iterator_before(multiset_iterator_t it_first, multiset_iterator_t it_second);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_ITERATOR_H_ */
/** eof **/

